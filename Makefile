ImageProccesTask: ImageProcessTask.cpp MyOpenCV.cpp Image.cpp
				gcc -o ImageProcessTask ImageProcessTask.cpp MyOpenCV.cpp Image.cpp -I/usr/local/include/  -L/usr/lib/ -lstdc++ -L/usr/local/lib -lopencv_highgui -lopencv_imgcodecs -lopencv_core -std=c++11   

