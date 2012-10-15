#ifndef CLIENT_H
#define CLIENT_H
#include "rbSimulator/config.h"
#include <stdio.h>
#include <string>
#include "netraw.h"
#include "comdef.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

namespace Simulator
{
   ///Class for client
	class Client
  {
  private:
    static const int    MaxDataGramSize = 65536;

    char                in_buffer[MaxDataGramSize];
    int                 port;
    std::string         address;
    std::string         inter_face;
    Net::UDP            multiCast;
    long int            frameNo;
    int                 tcapture;
    SSL_DetectionFrame  dframe;
    SSL_DetectionBall*  ball;
    SSL_DetectionRobot* bot[BlueTeam::SIZE + YellowTeam::SIZE];

  public:
    SSL_DetectionFrame* nframe;
    SSL_GeometryData*   gdata;
	
	
    Client(int port = Simulator::VISION_PORT,
           std::string address = Simulator::ADDRESS,
           std::string inter_face = Simulator::INTER_FACE);
		   
     ///DEstructor for client      
    ~Client();
    /** opens a multi cast connection
	 * @param block Boolean type
	 * @return true if cast connection successfull*/
    bool openMulticast(bool block = false);
    
    void closeMulticast();
    /** checks is a valid packed has been recieved from ssl vision.
    @param packet Object->SSLWrapperPacket , represnts latest data 
    @return true for valid packet */
    bool receive(SSL_WrapperPacket& packet);
    /**updates bot parameters from ssl vision.
    *@param teamColor enum for color of the team
     *@param botID integer type to hold ID of bot
    *@param x  float type to hold x coordinate of bot
	* @param y float type to hold y coordinate of position
	* @param orientation float type variable to hold slope of the bot*/
    void updateBot(TeamColor teamColor, int botID, float x, float y, float orientation);
	
    /**Update ball parameters
    *@param x float type
    *@param y float type*/
    void updateBall(float x, float y);
  }; // class Client
} // namespace Strategy

#endif // CLIENT_H