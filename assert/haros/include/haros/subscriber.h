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
  template<class M>
  class Subscriber
  {
  public:
    //---------------------------------------------------------------------------
    // Constructors and Destructors
    //---------------------------------------------------------------------------

    Subscriber() {}

    Subscriber(const ros::Subscriber& sub)
    : ros_sub_(sub)
    {
      if (sub)
      {
        history_sub_ = History<M>::instance.subscribe(sub.getTopic());
      }
    }

    Subscriber(const Subscriber<M>& rhs)
    : ros_sub_(rhs.ros_sub_), history_sub_(rhs.history_sub_)
    {}

    ~Subscriber() {}

    //---------------------------------------------------------------------------
    // HAROS Interface
    //---------------------------------------------------------------------------

    MessageEvent<M> lastReceive()
    {
      return History<M>::instance.lastReceive(getTopic());
    }

    typename M::ConstPtr lastMessage()
    {
      return lastReceive().msg;
    }

    //---------------------------------------------------------------------------
    // ROS Subscriber Interface
    //---------------------------------------------------------------------------

    /**
     * \brief Unsubscribe the callback associated with this Subscriber
     *
     * This method usually does not need to be explicitly called,
     * as automatic shutdown happens when
     * all copies of this Subscriber go out of scope
     *
     * This method overrides the automatic reference counted unsubscribe,
     * and immediately unsubscribes the callback associated with this Subscriber
     */
    void shutdown()
    {
      ros_sub_.shutdown();
    }

    std::string getTopic() const
    {
      return ros_sub_.getTopic();
    }

    /**
     * \brief Returns the number of publishers this subscriber is connected to
     */
    uint32_t getNumPublishers() const
    {
      return ros_sub_.getNumPublishers();
    }

    operator void*() const
    {
      return (void *) ros_sub_;
    }

    bool operator<(const ros::Subscriber& rhs) const
    {
      return ros_sub_ < rhs;
    }

    bool operator<(const Subscriber& rhs) const
    {
      return ros_sub_ < rhs.ros_sub_;
    }

    bool operator==(const ros::Subscriber& rhs) const
    {
      return ros_sub_ == rhs;
    }

    bool operator==(const Subscriber& rhs) const
    {
      return ros_sub_ == rhs.ros_sub_;
    }

    bool operator!=(const ros::Subscriber& rhs) const
    {
      return ros_sub_ != rhs;
    }

    bool operator!=(const Subscriber& rhs) const
    {
      return ros_sub_ != rhs.ros_sub_;
    }

  private:
    ros::Subscriber ros_sub_;

    typename History<M>::HolderPtr history_sub_;
  };
} // namespace haros

#endif // HAROS_ASSERT_SUBSCRIBER_H
