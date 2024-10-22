//
// Generated file, do not edit! Created by opp_msgtool 6.0 from frame_BB.msg.
//

#ifndef __FRAME_BB_M_H
#define __FRAME_BB_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class frame_BB;
/**
 * Class generated from <tt>frame_BB.msg:15</tt> by opp_msgtool.
 * <pre>
 * //
 * // This program is free software: you can redistribute it and/or modify
 * // it under the terms of the GNU Lesser General Public License as published by
 * // the Free Software Foundation, either version 3 of the License, or
 * // (at your option) any later version.
 * // 
 * // This program is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * // GNU Lesser General Public License for more details.
 * // 
 * // You should have received a copy of the GNU Lesser General Public License
 * // along with this program.  If not, see http://www.gnu.org/licenses/.
 * //
 * message frame_BB
 * {
 *     int source;
 *     int destination;
 *     int hopCount = 0;
 * }
 * </pre>
 */
class frame_BB : public ::omnetpp::cMessage
{
  protected:
    int source = 0;
    int destination = 0;
    int hopCount = 0;

  private:
    void copy(const frame_BB& other);

  protected:
    bool operator==(const frame_BB&) = delete;

  public:
    frame_BB(const char *name=nullptr, short kind=0);
    frame_BB(const frame_BB& other);
    virtual ~frame_BB();
    frame_BB& operator=(const frame_BB& other);
    virtual frame_BB *dup() const override {return new frame_BB(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getSource() const;
    virtual void setSource(int source);

    virtual int getDestination() const;
    virtual void setDestination(int destination);

    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const frame_BB& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, frame_BB& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline frame_BB *fromAnyPtr(any_ptr ptr) { return check_and_cast<frame_BB*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __FRAME_BB_M_H

