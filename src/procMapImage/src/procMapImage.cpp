#include "../include/procMapImage.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// pointer to our image processing class instance
ProcMapImage *proc_ptr;

/**
 * @brief a wrapper function for our standard OpenCV onclick event.
 * uses our class pointer to process the even in a ProcMapImage class 
 * context.
 * 
 * @param event the event the occurred.
 * @param x the x location of the click.
 * @param y the y location of the click.
*/
void ClickCallbackWrapper(int event, int x, int y, int flags, void* param) {
    if (event & cv::EVENT_LBUTTONDOWN) {
        proc_ptr->ClickCallback(x, y);
    }
}

void ProcMapImage::ClickCallback(int x, int y) {
    // Case: boundary selection
    if(this->_state_machine.getCurrentState() == BOUNDARY_SELECTION){

        // push back new points from the user
        _boundary_points.push_back(std::make_pair(x, y));

        // draw the point on the copy of the raw image
        cv::circle(this->_raw_map_draw_copy, cv::Point(x, y), 5, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_AA);

        // set flag when we get all our boundary points
        if(_boundary_points.size() == 4){
            this->_got_boundary = true;
        }
    }
}

ProcMapImage::ProcMapImage(cv::Mat raw_map){
    this->_raw_map = raw_map.clone();
    _got_boundary = false;
    proc_ptr = this;
    cv::namedWindow("map processing");
    cv::setMouseCallback("map processing", ClickCallbackWrapper, NULL);
}

mapData_t ProcMapImage::RunImageProc(){
    while(!this->SelectMapBoundary()){}

    _state_machine.advanceStateMachine();

    while(!this->SelectKnownScale()){}

    _state_machine.advanceStateMachine();

    while(!this->SelectText()){}

    _state_machine.advanceStateMachine();

    while(!this->SelectDoors()){}

    _state_machine.advanceStateMachine();

    mapData_t map_data = this->GenerateMapData();

    _state_machine.advanceStateMachine();

    return map_data;
}

bool ProcMapImage::SelectMapBoundary(){
    // make clone of original image for drawing purposes
    this->_raw_map_draw_copy = this->_raw_map.clone();

    // capture crop region from user
    std::cout << "Select map boundary by clicking on image" << std::endl;
    while (!this->_got_boundary)
    {
        cv::imshow("map processing", this->_raw_map_draw_copy);
        cv::waitKey(1);
    }

    // find boundaries of selected rectangle 
    auto min_x_val_pair = min_element(_boundary_points.begin(), _boundary_points.end(), 
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first < b.first;
    });

    auto min_y_val_pair = min_element(_boundary_points.begin(), _boundary_points.end(), 
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });

    auto max_x_val_pair = min_element(_boundary_points.begin(), _boundary_points.end(), 
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first > b.first;
    });

    auto max_y_val_pair = min_element(_boundary_points.begin(), _boundary_points.end(), 
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    });

    int min_x = min_x_val_pair->first;
    int max_x = max_x_val_pair->first;
    int min_y = min_y_val_pair->second;
    int max_y = max_y_val_pair->second;

    // perform crop operation
    cv::Rect crop_region(cv::Point(min_x, min_y), cv::Point(max_x, max_y));
    this->_cropped_map = this->_raw_map(crop_region);

    // make sure crop looks good to user
    std::cout << "Does the crop look correct? (Y/n)" << std::endl;
    cv::imshow("map processing", this->_cropped_map);
    char crop_correct = cv::waitKey(0);

    if(crop_correct == 'n' || crop_correct == 'N'){
        this->_got_boundary = false;
        this->_boundary_points.clear();
        return false;
    }
    else{
        return true;
    }
}

bool ProcMapImage::SelectKnownScale(){
    // TODO: implement me
    return true;
}

bool ProcMapImage::SelectText(){
    // TODO: implement me
    return true;
}

bool ProcMapImage::SelectDoors() {
    // TODO: implement me
    return true;
}

mapData_t ProcMapImage::GenerateMapData() {
    // TODO: implement me
    mapData_t test;
    return test;
}