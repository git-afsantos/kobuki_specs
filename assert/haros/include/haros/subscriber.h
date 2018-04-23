/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2018, Andre Santos
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
********************************************************************/

#ifndef HAROS_ASSERT_SUBSCRIBER_H
#define HAROS_ASSERT_SUBSCRIBER_H

#include <string>

#include <boost/shared_ptr.hpp>

#include <ros/ros.h>

#include "haros/history.h"

namespace haros
{
  class NodeHandle;

  class Subscriber : public ros::Subscriber
  {
  public:
    Subscriber() {};
    Subscriber(const ros::Subscriber& rhs);
    Subscriber(const Subscriber& rhs);
    ~Subscriber();

    MessageEvent lastReceive()
    {
      return History::instance.lastReceive(getTopic());
    }

    template<class M>
    boost::shared_ptr<M> lastMessage()
    {
      return lastReceive().msg<M>();
    }

  private:
    Subscriber(const ros::Subscriber& main_sub,
               const boost::shared_ptr<ros::Subscriber>& history_sub);

    boost::shared_ptr<ros::Subscriber> history_sub_;

    friend NodeHandle;
  };
} // namespace haros

#endif // HAROS_ASSERT_SUBSCRIBER_H