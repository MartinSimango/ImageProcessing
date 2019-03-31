ImageProccesTask: ImageProcessTask.cpp MyOpenCV.cpp Image.cpp
				gcc -o ImageProcessTask ImageProcessTask.cpp MyOpenCV.cpp Image.cpp -I/usr/local/Cellar/opencv/5.0.1/include/ -I/usr/local/Cellar/opencv/4.0.1/include/opencv4/ -L/usr/lib/ -lstdc++ -L/usr/local/lib -lopencv_highgui -lopencv_core -std=c++11   

