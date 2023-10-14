#include "../include/cmdLineArgHandler.h"
#include <filesystem>
#include <iostream>
#include <map>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

void CommandLineArgHandler::printUsageMenu() {
  std::cout << std::endl;
  std::cout << "usage: ./floorPlanToMap <path>" << std::endl;
  std::cout
      << "please replace <path> with path to an image or directory of images."
      << std::endl;
}

std::map<std::string, cv::Mat>
CommandLineArgHandler::parseCommandLineArgs(char **argv) {
  // generate map of images to process
  std::map<std::string, cv::Mat> image_file_map;
  std::string provided_path_str = argv[1];
  const std::filesystem::path file_path(provided_path_str);

  // if we are given an image, just push that into the map
  if (std::filesystem::is_regular_file(file_path)) {
    image_file_map[provided_path_str] = cv::imread(provided_path_str);
  }

  // otherwise, grab images from directory
  else if (std::filesystem::is_directory(file_path)) {

    // loop through all files in directory
    for (auto entry : std::filesystem::directory_iterator(file_path)) {

      // if we get a valid image, load it
      if (isValidFormat(entry.path())) {
        std::string cur_path_string = entry.path().string();
        image_file_map[cur_path_string] = cv::imread(cur_path_string);
      }
    }
  }

  return image_file_map;
}

bool CommandLineArgHandler::isValidFormat(std::filesystem::path provided_path) {
  bool in_list = false;

  // see if any elements in the provided file extension list
  // match the current file under test.
  for (size_t i = 0; i < this->acceptable_formats.size(); i++) {
    if (this->acceptable_formats[i] == provided_path.extension()) {
      in_list = true;
      break;
    }
  }

  return in_list;
}
