/**
 * @file Banner.h
 * @author Frederick Fan
 *
 * Class for the banner component of a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BANNER_H
#define CANADIANEXPERIENCE_MACHINELIB_BANNER_H

#include "Component.h"


/** Class for the banner component */
class Banner : public Component
{
private:

    /// The basic texture image we load for the banner
    std::unique_ptr<wxImage> mBannerImage = nullptr;

    /// The graphics bitmap we actually draw for the banner
    wxGraphicsBitmap mBannerGraphicsBitmap;

    /// The basic texture image we load for the scroll
    std::unique_ptr<wxImage> mRollImage = nullptr;

    /// The graphics bitmap we actually draw for the scroll
    wxGraphicsBitmap mRollGraphicsBitmap;

    ///The position of the banner
    wxPoint2DDouble mBannerPosition = wxPoint2DDouble(0,0);

    ///Position of the roll
    wxPoint2DDouble mRollOffsetByBannerPosition = wxPoint2DDouble(0,0);


public:


    Banner(const std::wstring& bannerImage, const std::wstring& rollImage);

    /// Destructor
    virtual ~Banner() {}

    /** Copy constructor disabled */
    Banner(const Banner &) = delete;

    /** Assignment operator disabled */
    void operator=(const Banner &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void ResetComponent() override;


    void SetPosition(wxPoint2DDouble point);

    void UpdateTime(double time) override;


};

#endif //CANADIANEXPERIENCE_MACHINELIB_BANNER_H
