#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

#include <iostream>
#include <vector>
#include "./BPA/BallPivotingAlgorithm.h"
#include "./rply/rply.h"
#include <unordered_map>
#include <chrono>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>



int display_rate = 1;



double x, y, z, nx, ny, nz;

//same as the instructions in RPIy...
static int vertex_cb(p_ply_argument argument) {
  std::vector<BPA::Point>* points;
  long index;
  ply_get_argument_user_data(argument, (void**)&points, &index);
  double v = ply_get_argument_value(argument);
  switch (index)
  {
    case 0:
      x = v;
      break;
    case 1:
      y = v;
      break;
    case 2:
      z = v;
      break;
    case 3:
      nx = v;
      break;
    case 4:
      ny = v;
      break;
    case 5:
      nz = v;
      points->emplace_back(BPA::Point{{x, y, z}, {nx, ny, nz}});
      break;
  }
  return 1;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

// camera
Camera camera(glm::vec3(0.0225653f, 0.196256f, 0.0195606f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float LastTime = 0.0f;

int main()
{
    const char * input_path = R"(..\input\bunny.ply)";
    const char * output_path = R"(..\output\bunny_0.ply)";
    // const char * input_path = R"(ply\cube.ply)";
    // const char * output_path = R"(output\cube_0.ply)";
    std::vector<BPA::Point> points;

    //parse the input file, store the points into a vector 
    p_ply input = ply_open(input_path, NULL, 0, NULL);
    if (!input) return 1;
    if (!ply_read_header(input)) return 1;
    ply_set_read_cb(input, "vertex", "x", vertex_cb, &points, 0);
    ply_set_read_cb(input, "vertex", "y", vertex_cb, &points, 1);
    ply_set_read_cb(input, "vertex", "z", vertex_cb, &points, 2);
    ply_set_read_cb(input, "vertex", "nx", vertex_cb, &points, 3);
    ply_set_read_cb(input, "vertex", "ny", vertex_cb, &points, 4);
    ply_set_read_cb(input, "vertex", "nz", vertex_cb, &points, 5);
    if (!ply_read(input)) return 1;
    ply_close(input);

    //set the ball's radius
    double radius = 0.002;
    std::cout<<"input radius:";
    std::cin>>radius;
    std::cout<<"radius is"<< radius <<std::endl;

    //do the BPA reconstrcution, which returns faces in a vector, record the elapsed time
    auto start = std::chrono::system_clock::now();
    std::vector<BPA::Triangle> triangles = BPA::reconstruct(points, radius);
    auto end = std::chrono::system_clock::now();
    std::cout<<"time spent:"<< std::chrono::duration_cast<std::chrono::milliseconds>
    (end-start).count()<< "ms" <<std::endl;

    //use an map to store all the points number in INT form, which makes the output process easier
    std::unordered_map<glm::vec3, int> um;
    for (int i = 0; i < points.size(); i++) {
        um[points[i].pos] = i;
    }

    //store faces
    std::vector<glm::ivec3> faces;
    for (auto triangle : triangles) {
        faces.emplace_back(um[triangle[0]], um[triangle[1]], um[triangle[2]]);
    }

    //write in the output file, we have vertex from points, and face from faces 
    std::ofstream output;
    output.open(output_path);
    output << "ply" << std::endl;
    output << "format ascii 1.0" << std::endl;
    output << "element vertex " << points.size() << std::endl;
    output << "property float x" << std::endl;
    output << "property float y" << std::endl;
    output << "property float z" << std::endl;
    output << "element face " << faces.size() << std::endl;
    output << "property list uchar int vertex_indices" << std::endl;
    output << "end_header" << std::endl;
    for (auto point : points) {
        output << point.pos.x << " " << point.pos.y << " " << point.pos.z << std::endl;
    }
    for (auto face : faces) {
        output << "3 " << face.x << " " << face.y << " " << face.z << std::endl;
    }
    output.close();
    std::cout<<"DONE"<<std::endl;


    // std::ofstream point_set;
    // point_set.open(R"(output\vertices.txt)");
    std::cout<<9*faces.size()<<std::endl;
    //store a vertex set for openGL buffer:
    float *vertices = new float[9*faces.size()]; // set up vertex data (and buffer(s)) and configure vertex attributes
    for (int i = 0;i<faces.size();i++){
      vertices[9*i+0]=points[faces[i].x].pos.x;
      vertices[9*i+1]=points[faces[i].x].pos.y;
      vertices[9*i+2]=points[faces[i].x].pos.z;
    //   point_set<<vertices[3*i+0]<<" ,"<<vertices[3*i+1]<<"  ,"<<vertices[3*i+2]<<"  ,"<< std::endl;
      vertices[9*i+3]=points[faces[i].y].pos.x;
      vertices[9*i+4]=points[faces[i].y].pos.y;
      vertices[9*i+5]=points[faces[i].y].pos.z;
    //   point_set<<vertices[3*i+3]<<" ,"<<vertices[3*i+4]<<" ,"<<vertices[3*i+5]<<" ,"<< std::endl;
      vertices[9*i+6]=points[faces[i].z].pos.x;
      vertices[9*i+7]=points[faces[i].z].pos.y;
      vertices[9*i+8]=points[faces[i].z].pos.z;
    //   point_set<<vertices[3*i+6]<<" ,"<<vertices[3*i+7]<<"  ,"<<vertices[3*i+8]<<"  ,"<< std::endl;
    }

    
    int size_of_vertices = 9*faces.size()*4;
    int vertices_numbers = 3*faces.size();
    std::cout<<size_of_vertices<<std::endl;


    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("../shader/shader.vs", "../shader/shader.fs");

    // modify camera infos
    camera.MovementSpeed = 0.3f;
    camera.Front = glm::vec3(-0.818379,-0.197657,-0.539618);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    // ourShader.setInt("texture1", 0);
    // ourShader.setInt("texture2", 1);


    // render loop
    // -----------
    glPointSize(4.0);
    glLineWidth(2.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int count = 0;
    glm::vec4 color1 = glm::vec4(0.1f, 0.4f, 0.2f, 1.0f);
    glm::vec4 color2 = glm::vec4(0.9f, 0.6f, 0.5f, 1.0f);
    glm::vec4 color3 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 color4 = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    while (!glfwWindowShouldClose(window))
    {
        if(count<vertices_numbers){
            if(LastTime>=0.1){
                count+=3*display_rate;
                LastTime=0;
            }
           
        }
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        LastTime+=deltaTime;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        
        ourShader.setMat4("model", model);
        
        glCullFace(GL_BACK);
        ourShader.setVec4("color", color1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, count);
        
        ourShader.setVec4("color", color2);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, count);

        glCullFace(GL_FRONT);
        ourShader.setVec4("color", color1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, count);
        
        ourShader.setVec4("color", color4);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, count);



        ourShader.setVec4("color", color3);
        glDrawArrays(GL_POINTS, 0, vertices_numbers);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        // std::cout<<"camera pos:"<<camera.Position[0]<<" "<<camera.Position[1]<<" "<<camera.Position[2]<<std::endl;
        // std::cout<<"camera front:"<<camera.Front[0]<<" "<<camera.Front[1]<<" "<<camera.Front[2]<<std::endl;
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        display_rate+=1;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}