#include <vector>
#include <opencv2/opencv.hpp>
#include <include/video/VideoAnalyser.h>
#include <include/detector/DetectorFactory.h>
#include <include/SharedFrame.h>
#include <include/video/VideoHandler.h>
#include <include/configuration/RobotConfiguration.h>
#include <include/controller/RobotControllerFactory.h>
#include <include/network/SimulationServiceImpl.h>
#include <include/network/RobotServer.h>
#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <include/controller/ThymioOAController.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
    Controller_type robo_type = ThymioObstacleAvoidance;
    std::vector<std::unique_ptr<RobotController>> controllers;
    std::vector<std::unique_ptr<QThread>> q_threads;
    int num_robots = 200;
    int base_port = 33333;
    QCoreApplication app(argc, argv);

    for (int i = 0; i < num_robots; ++i) {
        RobotConfig robot_config;
        robot_config.set("ip", "127.0.0.1");
        robot_config.set("port", to_string(base_port));
        robot_config.set("aesl_file", "../res/config/OAThymio.aesl");
        base_port++;

        // Launch the shared frame structure and the Detector factory
        RobotControllerFactory robot_controller_factory;
        //auto robot_controller = robot_controller_factory.make_shared_robot_controller(Thymio);
        controllers.emplace_back(robot_controller_factory.make_unique_robot_controller(robo_type,
                                                                                      robot_config));


/*    RoboManager roboManager;
    roboManager.register(robot_controller);
    roboManager.run();
    roboManager.stop();
*/

        if (robo_type == ThymioObstacleAvoidance) {
            auto thymioController = dynamic_cast<ThymioOAController*>(controllers.back().get());
            thymioController->start();
            q_threads.emplace_back(make_unique<QThread>());
            thymioController->moveToThread(q_threads.back().get());
        }
    }

    for (auto& thread : q_threads) {
        QTimer::singleShot(300000, thread.get(), SLOT(quit()));
        q_threads.back()->start();
        thread->start();
    }

    return app.exec();

    /*vector<unique_ptr<RobotController> controllers;
    vector<unique_ptr<QThread>> q_threads;

    // Initialize
    for (const auto& port : ports) {
        controllers.emplace_back(make_unique<TestController>(ip, port, aesl));
        controllers.back()->run();
        // store new thread and move the latest controller into it
        q_threads.emplace_back(make_unique<QThread>());
        controllers.back()->moveToThread(q_threads.back().get());
    }

    // Fire them up
    for (auto& q_thread : q_threads) {
        QTimer::singleShot(300000, q_thread.get(), SLOT(quit()));
        q_thread->start();
    }*/


    /*SimulationServiceImpl simulationService;
    simulationService.sink(robot_controller);
    RobotServer server{"127.0.0.1:30000"};
    server.register_service(simulationService);
    server.start();
    */
    /*
    DetectorFactory dec_factory;
    auto shared_detector = shared_ptr<Detector>(move(dec_factory.make_detector(Robot)));
    shared_detector->initialize("emergent_controller/res/images/object.jpg");
    robot_controller->set_shared_detector(shared_detector);

    shared_ptr<FrameStructure> shared_frame = make_shared<SharedFrame>();
    auto video_handler = VideoHandler{shared_frame};
    // move a new detector to the videoanalyser and take copy of the shared structure
    auto video_analyser = VideoAnalyser{shared_detector, shared_frame, video_handler.get_frame_size()};

    // Launches a thread that retrieves images from the camera and puts them into the shared structure
    video_handler.start();
    // Launches a thread that continously pulls images from the shared structure and tries to detect an entity within the image
    video_analyser.start();
     */
    // Launches a thread that controls how the robot operates
    /*robot_controller->start();

    this_thread::sleep_for(300s);
    robot_controller->stop(); // Stops the execution and joins the thread
    /* video_analyser.stop();
    video_handler.stop();
    */

    //server.stop();
    //cout << "Main Finished" << "\n";
    //return 0;
}