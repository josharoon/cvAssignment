
#ifndef VIDEORECODER_CONTOUR_H
#define VIDEORECODER_CONTOUR_H
#include "edgeGeo.h"

/**
 * detects contours and events based on their detection
 */
class contour : public edgeGeo {
public:
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    std::vector<std::vector<Point>>contourPoly;
    std::vector<RotatedRect> boundRect;
    std::vector<Point2f>centers;
    std::vector<float>radius;

    void aproximateContours();

    [[maybe_unused]] void discardContours();
    /**
     * detect contours in image
     */
    void detect() override;
    /**
     * draw contours for visualisation
     */
    void draw() override;
    /**
     * detect vehicle event based on area threshold
     */
    void detectVehicleEvent();
    /**
     * detect train event based on both area of contour and angle of bounding box.
     */
    void detectTrainEvent();
    /**
     * set minimum area for train theshold
     */
    void setTrainAreaThreshold(int trainAreaThreshold);
    /**
     * sets an angle range for the train orientation
     * @param min  angle in deg
     * @param max angle in deg
     */
    void setAngleTolerance(double min , double max);
    /**
     * returns number of vehicle detection events.
     */
    int getVehicleEvents() const;
    /**
     * returns number of train detection events.
     */
    int getTrainEvents() const;
    /**
     * min area for vehicle threshold
     */
    void setAreaThreshold(int areaThreshold);
    /**
     *draw boxes of detected events for visualisation.
     *@param i boundRectangle index to draw
     * @param color 8bit bgr color value.
     */
    void drawEventBox(size_t i, Scalar_<int> color);

private:
    int vehicleAreaThreshold;
    int trainAreaThreshold;
    int vehicleEvents=0;
    int trainEvents=0;
    double minAngle;
    double maxAngle;
};


#endif //VIDEORECODER_CONTOUR_H
