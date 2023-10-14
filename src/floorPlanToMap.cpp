#include "cmdLineArgHandler/include/cmdLineArgHandler.h"

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
    // TODO: process images here.
  }

  return 0;
}