#include "cmdLineArgHandler/include/cmdLineArgHandler.h"
#include "procMapImage/include/procMapImage.h"

int main(int argc, char **argv) {
  // process command line arguments
  CommandLineArgHandler cmd_arg_handler;
  if (argc < 2) {
    std::cerr
        << "You must provide path to a directory of images, or a single image!"
        << std::endl;
    cmd_arg_handler.printUsageMenu();
    return -1;
  }

  std::map<std::string, cv::Mat> img_map =
      cmd_arg_handler.parseCommandLineArgs(argv);

  // for each provided image, perform processing procedure
  for (auto elem : img_map) {
    ProcMapImage image_proc(elem.second);
    mapData_t map_data = image_proc.RunImageProc();

    // TODO: implement function to save map image and metadata
    // in ROS format
  }

  return 0;
}