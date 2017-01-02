#ifndef SCHEDULER_INTERFACE_H_
#define SCHEDULER_INTERFACE_H_

namespace HomeAutomation
{


/**
  * @brief Interface for scheduler
  * A scheduler can be waked up by some kind of timer or similiar service
  */
class IScheduler
{
public:
    /**
     * @brief ~IScheduler
     */
    virtual ~IScheduler ()
    {}

    /**
     * @brief Wakeup the scheduler up
     */
    virtual void wakeup () = 0;

protected:
    /**
     * Assignment of abstract type is not allowed
    */
    IScheduler & operator= (const IScheduler &);
};


} // namespace HomeAutomation



#endif //SCHEDULER_INTERFACE_H_
