# Your company built an in-house calendar tool called HiCal. You want to add a feature to see the times in a day when everyone is available.

To do this, you’ll need to know when any team is having a meeting. In HiCal, a meeting is stored as an instance of a Meeting class with integer member variables startTime and endTime. These integers represent the number of 30-minute blocks past 9:00am.

```c++
class Meeting
{
private:
        // number of 30 min blocks past 9:00 am
        unsigned int startTime_;
        unsigned int endTime_;

public:
    Meeting() :
        startTime_(0),
        endTime_(0)
    {
    }

    Meeting(unsigned int startTime, unsigned int endTime) :
        startTime_(startTime),
        endTime_(endTime)
    {
    }

    unsigned int getStartTime() const
    {
        return startTime_;
    }

    void setStartTime(unsigned int startTime)
    {
        startTime_ = startTime;
    }

    unsigned int getEndTime() const
    {
        return endTime_;
    }

    void setEndTime(unsigned int endTime)
    {
        endTime_ = endTime;
    }

    bool operator==(const Meeting& other) const
    {
        return
            startTime_ == other.startTime_
            && endTime_ == other.endTime_;
    }
};
```
For example:
```c++
Meeting meeting1(2, 3);  // meeting from 10:00 – 10:30 am
Meeting meeting2(6, 9);  // meeting from 12:00 – 1:30 pm
```
Write a function mergeRanges() that takes a vector of meeting time ranges and returns a vector of condensed ranges.

For example, given:
```c++
  [Meeting(0, 1), Meeting(3, 5), Meeting(4, 8), Meeting(10, 12), Meeting(9, 10)]
```
your function would return:
```c++
  [Meeting(0, 1), Meeting(3, 8), Meeting(9, 12)]
```
**Do not assume the meetings are in order.** The meeting times are coming from multiple teams.

**Write a solution that's efficient even when we can't put a nice upper bound on the numbers representing our time ranges.** Here we've simplified our times down to the number of 30-minute slots past 9:00 am. But we want the function to work even for very large numbers, like Unix timestamps. In any case, the spirit of the challenge is to merge meetings where startTime and endTime don't have an upper bound.

### Gotchas

```c++
[Meeting(1, 2), Meeting(2, 3)]
```
These meetings should probably be merged, although they don't exactly "overlap"—they just "touch."

Look at this case:
```c++
  [Meeting(1, 5), Meeting(2, 3)]
```
Notice that although the second meeting starts later, it ends before the first meeting ends. Does your function correctly handle the case where a later meeting is "subsumed by" an earlier meeting?

Look at this case:
```c++
  [Meeting(1, 10), Meeting(2, 6), Meeting(3, 5), Meeting(7, 9)]
```
Here all of our meetings should be merged together into just Meeting(1, 10). We need keep in mind that after we've merged the first two we're not done with the result—the result of that merge may itself need to be merged into other meetings as well.

Make sure that your function won't "leave out" the last meeting.

We can do this in O(nlgn) time.

## Solution

First, we sort our input vector of meetings by start time so any meetings that might need to be merged are now next to each other. Then we walk through our sorted meetings from left to right. At each step, either:

1. We can merge the current meeting with the previous one, so we do.
2. We can't merge the current meeting with the previous one, so we know the previous meeting can't be merged with any future meetings and we throw the current meeting into mergedMeetings.

```c++
// supplementary function for arranging Meeting objects by start time ascending
bool meetingComparisonFunction(
    const Meeting& firstMeeting,
    const Meeting& secondMeeting)
{
    return firstMeeting.getStartTime() < secondMeeting.getStartTime();
}

vector<Meeting> mergeRanges(const vector<Meeting>& meetings)
{
    // sort by start time
    vector<Meeting> sortedMeetings(meetings);
    sort(sortedMeetings.begin(), sortedMeetings.end(), meetingComparisonFunction);

    // initialize mergedMeetings with the earliest meeting
    vector<Meeting> mergedMeetings;
    mergedMeetings.push_back(sortedMeetings.front());

    for (const Meeting& currentMeeting : sortedMeetings) {

        Meeting& lastMergedMeeting = mergedMeetings.back();

        // if the current and last meetings overlap, use the latest end time
        if (currentMeeting.getStartTime()
            <= lastMergedMeeting.getEndTime()) {
            lastMergedMeeting.setEndTime(max(lastMergedMeeting.getEndTime(),
                currentMeeting.getEndTime()));
        }
        else {
            // add the current meeting since it doesn't overlap
            mergedMeetings.push_back(currentMeeting);
        }
    }

    return mergedMeetings;
}
```

## Complexity

O(nlgn) time and O(n) space.

Even though we only walk through our vector of meetings once to merge them, we sort all the meetings first, giving us a runtime of O(nlgn). It's worth noting that if our input were sorted, we could skip the sort and do this in O(n) time!

We create a new vector of merged meeting times. In the worst case, none of the meetings overlap, giving us a vector identical to the input vector. Thus we have a worst-case space cost of O(n).

### Follow-ups

1. What if we did have an upper bound on the input values? Could we improve our runtime? Would it cost us memory?
2. Could we do this "in-place" on the input vector and save some space? What are the pros and cons of doing this in-place?

This one arguably uses a greedy ↴ approach as well, except this time we had to sort the vector first.

How did we figure that out?

We started off trying to solve the problem in one pass, and we noticed that it wouldn't work. We then noticed the reason it wouldn't work: to see if a given meeting can be merged, we have to look at all the other meetings! That's because the order of the meetings is random.

That's what got us thinking: what if the vector were sorted? We saw that then a greedy approach would work. We had to spend O(nlgn) time on sorting the vector, but it was better than our initial brute force approach, which cost us O(n^2) time!
