/**
 * @file Banner.cpp
 * @author Frederick Fan
 *
 * Class for the banner component
 */

#include "pch.h"
#include "Banner.h"


/// Scale to draw relative to the image sizes
const double BannerScale = 0.42;

/// Height of the banner in pixels
double const BannerHeight = 150 * BannerScale;

/// Width fo the banner in pixels
const double BannerWidth = 1024 * BannerScale;

/// Height of the banner roll image in pixels
const double BannerRollHeight = 300 * BannerScale;

/// Width of the banner roll image in pixels
double const BannerRollWidth = 16 * BannerScale;

/// How fast the banner will unfurl at each time update
double const BannerSpeed = 4;

/// Minimum number of pixels to start with as unfurled
const double BannerMinimum = 15;

/**
 * Constructor
 * @param bannerImage the file path for the banner image
 * @param rollImage the file path for the roll image
 */
Banner::Banner(const std::wstring& bannerImage, const std::wstring& rollImage)
{
    mBannerImage = std::make_unique<wxImage>(bannerImage);
    mRollImage = std::make_unique<wxImage>(rollImage);

}

/**
 * Draw the banner
 * @param graphics the context to draw on
 */
void Banner::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    //How I am handling the unfurling banner is that I have a position stored for where the roll should be,
    //and then I am gonna draw the banner so that the banner will be draw to the right of the roll
    //and that right side of the roll is going to be clipped off so that the rest of the banner can not be seen
    //and then the banner's x position will be updated with each time update, and the banner is being drawn at its
    //position relative to the roll position. Then I will have a condition to make sure that the position will not
    //go past the roll's position minus the banner width, commenting out the clip statement might give a
    //better idea of what I mean

    graphics->PushState();
    graphics->Translate(mRollOffsetByBannerPosition.m_x, mRollOffsetByBannerPosition.m_y);
    graphics->Scale(BannerScale,-BannerScale);

    if(mBannerGraphicsBitmap.IsNull())
    {
        mBannerGraphicsBitmap = graphics->CreateBitmapFromImage(*mBannerImage);
    }
    if(mRollGraphicsBitmap.IsNull())
    {
        mRollGraphicsBitmap = graphics->CreateBitmapFromImage(*mRollImage);
    }

    graphics->Clip(BannerRollWidth, 0, BannerWidth,BannerHeight);
    graphics->DrawBitmap( mBannerGraphicsBitmap, mBannerPosition.m_x-mRollOffsetByBannerPosition.m_x, 0,
                          BannerWidth, BannerHeight);
    graphics->DrawBitmap(mRollGraphicsBitmap, BannerWidth, -BannerHeight/2, //using constant just to take 1/2 height
                         BannerRollWidth, BannerRollHeight);
    graphics->PopState();



}

/**
 * Reset the banner component
 */
void Banner::ResetComponent()
{
    //This is the initial value I want, so I reset it to this value
    mBannerPosition.m_x = mRollOffsetByBannerPosition.m_x + BannerWidth - BannerMinimum;
}

/**
 * Handle each time update
 * @param time the time to add
 */
void Banner::UpdateTime(double time)
{
    Component::UpdateTime(time);


    if (mBannerPosition.m_x-BannerSpeed >= mRollOffsetByBannerPosition.m_x)
    {
        mBannerPosition.m_x -= BannerSpeed;
    }
    else
    {
        mBannerPosition.m_x = mRollOffsetByBannerPosition.m_x;
    }
}

/**
   * Set the position
   * @param point the point to set the position to
   */
void Banner::SetPosition(wxPoint2DDouble point)
{

    //with how I am handling the banner class, the banner position that is being set represents the point at
    //the leftmost part of the banner image after the animation is done
    mBannerPosition.m_x = point.m_x + BannerWidth - BannerMinimum;
    mBannerPosition.m_y = point.m_y;

    //This position represents the roll before it is offset by the banner, when it is drawn the position will be
    //offset by the banner size and height
    mRollOffsetByBannerPosition = point;
}

