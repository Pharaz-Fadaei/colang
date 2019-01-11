#ifndef VALUE_H_
#define VALUE_H_

#include <string>
#include <map>


enum ValueType
{
    INTEGRAL_VALUE,
    BOOLEAN_VALUE,
    DOUBLE_VALUE,
    STRING_VALUE,
    ARRAY_VALUE,
    EMPTY_VALUE
};

enum SimpleValueType
{
    SIMPLE_NUMERIC_VALUE,
    SIMPLE_STRING_VALUE,
    SIMPLE_ARRAY_VALUE
};




class Value
{
private:
  int integralValue = -1;
  std::string stringValue = "";
  bool booleanValue = false;
  double doubleValue = -1;
  std::map<Value, Value> values;
  ValueType type;

public:

    Value();
    Value(ValueType type);
    Value(std::string *str, bool parseToInt = false);
    Value(int i);
    Value(double x);
    Value(std::string str);
    Value(const Value& val);
    Value(std::string *s, ValueType type);









    void clearValues();
    void setIntegralValue(const int n);
    int getIntegralValue() const;
    void setStringValue(const std::string& str);
    std::string getStringValue() const;
    void setDoubleValue(const double d);
    double getDoubleValue() const;
    void setArrayValue(const Value& index, const Value& value);
    void setArrayIndexedValue(const Value& value);
    Value getArrayValue(const Value& index);
    const std::map<Value, Value>& getArray();
    void deleteArrayValue(const Value& index);
    bool containsKey(const Value& index);
    Value getKeys();
    int getArraySize() const;
    ValueType getType() const;
    void convertToArray();
    SimpleValueType getSimpleType() const;

    double getNumericValue() const;

    bool operator <(const Value& value) const;


    bool operator <=(const Value& value) const;


    bool operator >(const Value& value) const;

    bool operator >=(const Value& value) const;

    bool operator ==(const Value& value) const;
    Value operator +(const Value& value) const;


    Value operator -(const Value& value) const;

    Value operator *(const Value& value) const;


    Value operator /(const Value& value) const;


    Value operator %(const Value& value) const;

    Value negate() const;
    Value exponentiate(const Value& value) const;

    int toInt() const;

    double toDouble() const;

    std::string toString() const;


    std::string getTypeTitle() const;

    static std::string getTypeTitle(ValueType type)
    {
        switch(type)
        {
            case INTEGRAL_VALUE:
                return "integral";
                break;
            case BOOLEAN_VALUE:
                return "boolean";
                break;
            case DOUBLE_VALUE:
                return "double";
                break;
            case STRING_VALUE:
                return "string";
                break;
            case ARRAY_VALUE:
                return "array";
                break;
            case EMPTY_VALUE:
                return "empty";
                break;
        }        
    }

};



#endif