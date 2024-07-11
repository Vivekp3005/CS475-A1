#include"system1/particleSystem.h"
#include"system2/particleSystem2.h"
int getT(){
  time_t tim = time(0);
  tm *gottime = localtime(&tim);
  int sec = gottime->tm_sec;
  int min = gottime->tm_min;
  int hr = gottime->tm_hour;
  
  return (hr*60*60) + (min*60) + sec;
}

int main(int argc, char** argv)
{
  GLFWwindow* window;

  glfwSetErrorCallback(csX75::error_callback);

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  window = glfwCreateWindow(1000, 1000, "CS475 Assignment", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }

  glfwMakeContextCurrent(window);
  
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  glfwSetKeyCallback(window, csX75::key_callback);
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  csX75::initGL();
  ParSys* newSys = new ParSys();
  ParSys2* newSys2 = new ParSys2();
  newSys->initShaderGL();
  newSys->initVBSHGL();
  bool flag = 1;
  bool play = 1;

  float xPos = 0, yPos = 0, radius = 1.0f;

  while (glfwWindowShouldClose(window) == 0)
   {
      if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        newSys->initShaderGL();
        newSys->initVBSHGL();
        flag = 1;
      }
      else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        newSys2->initShaderGL2();
        newSys2->initVBSHGL2();
        flag = 0;
      }
      else if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
          play = 0;
          int curT = getT();
          if(flag){
            newSys->pause(curT);
          }
          else{
            newSys2->pause2(curT);
          }
      }
      else if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
          play = 1;
          if(flag){
            newSys->pau = 0;
          }
          else{
            newSys2->pau2 = 0;
          }
      }
      if(flag){
        newSys->renderGL();

        glfwSwapBuffers(window);

        glfwPollEvents();

        if(!newSys->pau){
          for(int i=0;i<newSys->storage.size();i++){
            if(getT() - newSys->storage[i]->timeOrigin >= 3.2){
              newSys->storage.erase(newSys->storage.begin()+i);
              i--;
            }
          }
        }
      }
      else{
        newSys2->renderGL2();

        glfwSwapBuffers(window);
      
        glfwPollEvents();

        if(!newSys2->pau2){
          for(int i=0;i<newSys2->storage2.size();i++){
            if(getT() - newSys2->storage2[i]->timeOrigin2 >= 3.9){
              newSys2->storage2.erase(newSys2->storage2.begin()+i);
              i--;
            }
          }
        }
      }
    }
  
  glfwTerminate();
  return 0;
}
