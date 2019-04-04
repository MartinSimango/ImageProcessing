ImageProccesTask: ImageProcessTask.cpp MyOpenCV.cpp Image.cpp
				g++ -o ImageProcessTask ImageProcessTask.cpp MyOpenCV.cpp Image.cpp -I/usr/local/include/  -L/usr/lib/ -lstdc++ -L/usr/local/lib -lopencv_highgui -lopencv_imgcodecs -lopencv_core -std=c++11 -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_videostab
				

