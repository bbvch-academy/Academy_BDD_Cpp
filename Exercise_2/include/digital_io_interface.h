#ifndef DIGITAL_IO_INTERFACE_H_
#define DIGITAL_IO_INTERFACE_H_

namespace HomeAutomation
{

/**
  * @brief Interface for a digital (binary) I/O of the home automation system
  */
class IDigitalIO
{
public:
    /**
     * @brief ~IDigitalIO
     */
    virtual ~IDigitalIO ()
    {}

    /**
     * @brief set the output
     * @param value output value
     */
    virtual void set (bool value) = 0;

    /**
       * @brief get the input value
       * @return current value of I/O
       */
    virtual bool get () const = 0;

protected:
    /**
     * Assignment of abstract type is not allowed
    */
    IDigitalIO & operator= (const IDigitalIO &);
};


} // namespace HomeAutomation



#endif //DIGITAL_IO_INTERFACE_H_
