#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <math.h>

#include "syntax_tree/value.h"
#include "utility.cpp"

Value::Value()
{
    this->type = EMPTY_VALUE;
}
Value::Value(ValueType type)
{
    this->type = type;
}
Value::Value(std::string *str, bool parseToInt /*=false*/)
{
    if (!parseToInt)
    {
        this->setStringValue(std::string(*str, 1, str->size() - 2));
        this->type = STRING_VALUE;
    }
    else
    {
        std::istringstream iss(*str);
        int n;
        iss >> n;
        this->integralValue = n;
        this->booleanValue = n;
        this->type = INTEGRAL_VALUE;
    }
    delete str;
}
Value::Value(int i)
{
    this->setIntegralValue(i);
}
Value::Value(double x)
{
    this->setDoubleValue(x);
}
Value::Value(std::string str)
{
    this->setStringValue(str);
}

Value::Value(const Value &val)
{
    this->integralValue = val.integralValue;
    this->stringValue = val.stringValue;
    this->booleanValue = val.booleanValue;
    this->doubleValue = val.doubleValue;
    this->type = val.type;
    this->values.insert(val.values.begin(), val.values.end());
}
Value::Value(std::string *s, ValueType type)
{
    switch (type)
    {
    case INTEGRAL_VALUE:
        this->setIntegralValue(Utility::StringToInt(*s));
        break;
    case DOUBLE_VALUE:
        this->setDoubleValue(Utility::StringToDouble(*s));
        break;
    case STRING_VALUE:
        std::string str = std::string(*s, 1, s->size() - 2);
        this->setStringValue(str);
        break;
    }
}

void Value::clearValues()
{
    this->stringValue = "";
    this->integralValue = -1;
    this->booleanValue = false;
    this->doubleValue = -1;
    this->values.clear();
}
void Value::setIntegralValue(const int n)
{
    this->clearValues();
    this->type = INTEGRAL_VALUE;
    this->integralValue = n;
}
int Value::getIntegralValue() const
{
    return this->integralValue;
}
void Value::setStringValue(const std::string &str)
{
    this->type = STRING_VALUE;
    this->clearValues();

    this->stringValue = str;
}
std::string Value::getStringValue() const
{
    return this->stringValue;
}
void Value::setDoubleValue(const double d)
{
    this->clearValues();
    this->type = DOUBLE_VALUE;
    this->doubleValue = d;
}
double Value::getDoubleValue() const
{
    return this->doubleValue;
}
void Value::setArrayValue(const Value &index, const Value &value)
{
    if (this->type != ARRAY_VALUE)
    {
        this->clearValues();
        this->type = ARRAY_VALUE;
    }
    this->values[index] = value;
}
void Value::setArrayIndexedValue(const Value &value)
{
    Value index((int)this->values.size());
    this->setArrayValue(index, value);
}
Value Value::getArrayValue(const Value &index)
{
    return this->values[index];
}
const std::map<Value, Value> &Value::getArray()
{
    return this->values;
}
void Value::deleteArrayValue(const Value &index)
{
    std::map<Value, Value>::iterator it = this->values.find(index);
    if (it != this->values.end())
        this->values.erase(it);
}
bool Value::containsKey(const Value &index)
{
    return this->values.find(index) != this->values.end();
}
Value Value::getKeys()
{
    Value v;
    for (std::map<Value, Value>::iterator it = this->values.begin(); it != this->values.end(); it++)
        v.setArrayIndexedValue(it->first);
    return v;
}
int Value::getArraySize() const
{
    return this->values.size();
}
ValueType Value::getType() const
{
    return this->type;
}
void Value::convertToArray()
{
    this->clearValues();
    this->type = ARRAY_VALUE;
}
SimpleValueType Value::getSimpleType() const
{
    return this->type <= DOUBLE_VALUE ? SIMPLE_NUMERIC_VALUE : (SimpleValueType)(this->type - 2);
}

double Value::getNumericValue() const
{
    if (this->getSimpleType() != SIMPLE_NUMERIC_VALUE)
        Utility::error("Value is not numeric.");

    switch (this->type)
    {
    case INTEGRAL_VALUE:
        return this->integralValue;
        break;
    case BOOLEAN_VALUE:
        return this->booleanValue;
        break;
    case DOUBLE_VALUE:
        return this->doubleValue;
        break;
    }
}

bool Value::operator<(const Value &value) const
{
    if (this->type != value.type)
        return this->type < value.type;

    switch (this->type)
    {
    case INTEGRAL_VALUE:
        return this->integralValue < value.integralValue;
        break;
    case BOOLEAN_VALUE:
        return this->booleanValue < value.booleanValue;
        break;
    case DOUBLE_VALUE:
        return this->doubleValue < value.doubleValue;
        break;
    case STRING_VALUE:
        return this->stringValue < value.stringValue;
    case ARRAY_VALUE:
        return this->values < value.values;
    }
}

bool Value::operator<=(const Value &value) const
{
    if (this->type != value.type)
        return this->type <= value.type;

    switch (this->type)
    {
    case INTEGRAL_VALUE:
        return this->integralValue <= value.integralValue;
        break;
    case BOOLEAN_VALUE:
        return this->booleanValue <= value.booleanValue;
        break;
    case DOUBLE_VALUE:
        return this->doubleValue <= value.doubleValue;
        break;
    case STRING_VALUE:
        return this->stringValue <= value.stringValue;
    case ARRAY_VALUE:
        return this->values <= value.values;
    }
}

bool Value::operator>(const Value &value) const
{
    if (this->type != value.type)
        return this->type > value.type;

    switch (this->type)
    {
    case INTEGRAL_VALUE:
        return this->integralValue > value.integralValue;
        break;
    case BOOLEAN_VALUE:
        return this->booleanValue > value.booleanValue;
        break;
    case DOUBLE_VALUE:
        return this->doubleValue > value.doubleValue;
        break;
    case STRING_VALUE:
        return this->stringValue > value.stringValue;
    case ARRAY_VALUE:
        return this->values > value.values;
    }
}

bool Value::operator>=(const Value &value) const
{
    if (this->type != value.type)
        return this->type >= value.type;

    switch (this->type)
    {
    case INTEGRAL_VALUE:
        return this->integralValue >= value.integralValue;
        break;
    case BOOLEAN_VALUE:
        return this->booleanValue >= value.booleanValue;
        break;
    case DOUBLE_VALUE:
        return this->doubleValue >= value.doubleValue;
        break;
    case STRING_VALUE:
        return this->stringValue >= value.stringValue;
    case ARRAY_VALUE:
        return this->values >= value.values;
    }
}

bool Value::operator==(const Value &value) const
{
    if (this->type != value.type)
        return false;

    switch (this->type)
    {
    case INTEGRAL_VALUE:
        return this->integralValue == value.integralValue;
        break;
    case BOOLEAN_VALUE:
        return this->booleanValue == value.booleanValue;
        break;
    case DOUBLE_VALUE:
        return this->doubleValue == value.doubleValue;
        break;
    case STRING_VALUE:
        return this->stringValue == value.stringValue;
    case ARRAY_VALUE:
        return this->getArraySize() == value.getArraySize() && std::equal(this->values.begin(), this->values.end(), value.values.begin());
    }
}
Value Value::operator+(const Value &value) const
{
    Value val;
    if (this->type == value.type)
    {
        switch (this->type)
        {
        case INTEGRAL_VALUE:
            val.setIntegralValue(this->integralValue + value.integralValue);
            break;
        case DOUBLE_VALUE:
            val.setDoubleValue(this->doubleValue + value.doubleValue);
            break;
        case STRING_VALUE:
            val.setStringValue(this->stringValue + value.stringValue);
            break;
        case ARRAY_VALUE:
            val = Value(*this);
            val.values.insert(value.values.begin(), value.values.end());
        }
    }
    else if (this->type == DOUBLE_VALUE && value.type == INTEGRAL_VALUE)
        val.setDoubleValue(this->doubleValue + (double)value.integralValue);
    else if (this->type == INTEGRAL_VALUE && value.type == DOUBLE_VALUE)
        val.setDoubleValue((double)this->integralValue + value.doubleValue);
    else if (this->type == INTEGRAL_VALUE && value.type == STRING_VALUE)
        val.setStringValue(Utility::IntToString(this->integralValue) + value.stringValue);
    else if (this->type == STRING_VALUE && value.type == INTEGRAL_VALUE)
        val.setStringValue(this->stringValue + Utility::IntToString(value.integralValue));
    else if (this->type == DOUBLE_VALUE && value.type == STRING_VALUE)
        val.setStringValue(Utility::DoubleToString(this->doubleValue) + value.stringValue);
    else if (this->type == STRING_VALUE && value.type == DOUBLE_VALUE)
        val.setStringValue(this->stringValue + Utility::DoubleToString(value.doubleValue));
    else
        Utility::error("Invalid addition of a(n) " + Value::getTypeTitle(this->getType()) + " and a(n) " + Value::getTypeTitle(value.getType()));

    return val;
}

Value Value::operator-(const Value &value) const
{
    Value val;
    if (this->type == value.type)
    {
        switch (this->type)
        {
        case INTEGRAL_VALUE:
            val.setIntegralValue(this->integralValue - value.integralValue);
            break;
        case DOUBLE_VALUE:
            val.setDoubleValue(this->doubleValue - value.doubleValue);
            break;
        }
    }
    if (this->type == DOUBLE_VALUE && value.type == INTEGRAL_VALUE)
        val.setDoubleValue(this->doubleValue - value.integralValue);
    else if (this->type == INTEGRAL_VALUE && value.type == DOUBLE_VALUE)
        val.setDoubleValue(this->integralValue - value.doubleValue);

    return val;
}

Value Value::operator*(const Value &value) const
{
    Value val;
    if (this->type == value.type)
    {
        switch (this->type)
        {
        case INTEGRAL_VALUE:
            val.setIntegralValue(this->integralValue * value.integralValue);
            break;
        case DOUBLE_VALUE:
            val.setDoubleValue(this->doubleValue * value.doubleValue);
            break;
        }
    }
    if (this->type == DOUBLE_VALUE && value.type == INTEGRAL_VALUE)
        val.setDoubleValue(this->doubleValue * value.integralValue);
    else if (this->type == INTEGRAL_VALUE && value.type == DOUBLE_VALUE)
        val.setDoubleValue(this->integralValue * value.doubleValue);

    return val;
}

Value Value::operator/(const Value &value) const
{
    Value val;
    if (this->type == value.type)
    {
        switch (this->type)
        {
        case INTEGRAL_VALUE:
            if (value.integralValue == 0)
                Utility::error("Division by zero!");
            val.setDoubleValue((double)this->integralValue / value.integralValue);
            break;
        case DOUBLE_VALUE:
            if (value.doubleValue == 0)
                Utility::error("Division by zero!");
            val.setDoubleValue(this->doubleValue / value.doubleValue);
            break;
        }
    }
    if (this->type == DOUBLE_VALUE && value.type == INTEGRAL_VALUE)
    {
        if (value.integralValue == 0)
            Utility::error("Division by zero!");
        val.setDoubleValue(this->doubleValue / value.integralValue);
    }
    else if (this->type == INTEGRAL_VALUE && value.type == DOUBLE_VALUE)
    {
        if (value.doubleValue == 0)
            Utility::error("Division by zero!");
        val.setDoubleValue(this->integralValue / value.doubleValue);
    }

    return val;
}

Value Value::operator%(const Value &value) const
{
    Value val;
    if (this->type == value.type)
    {
        switch (this->type)
        {
        case INTEGRAL_VALUE:
            if (value.integralValue == 0)
                Utility::error("Division by zero!");
            val.setIntegralValue(this->integralValue % value.integralValue);
            break;
        }
    }

    return val;
}

Value Value::negate() const
{
    Value val;
    switch(this->type)
    {
        case INTEGRAL_VALUE:
        val.setIntegralValue(-this->getIntegralValue());
        break;
        case DOUBLE_VALUE:
        val.setDoubleValue(-this->getDoubleValue());
    }
    return val;
}

Value Value::exponentiate(const Value &value) const
{
    Value val;
    val.setDoubleValue(pow(this->toDouble(), value.toDouble()));
    return val;
}

int Value::toInt() const
{
    int i;
    if (this->getType() == INTEGRAL_VALUE)
        i = this->getIntegralValue();
    else if (this->getType() == DOUBLE_VALUE)
        i = (int)this->getDoubleValue();
    else if (this->getType() == STRING_VALUE)
        i = Utility::StringToInt(this->getStringValue());
    else
        Utility::error("Cannot convert value to integer.");
    return i;
}

double Value::toDouble() const
{
    double x;
    if (this->getType() == INTEGRAL_VALUE)
        x = (double)this->getIntegralValue();
    else if (this->getType() == DOUBLE_VALUE)
        x = this->getDoubleValue();
    else if (this->getType() == STRING_VALUE)
        x = Utility::StringToDouble(this->getStringValue());
    else
        Utility::error("Cannot convert value to double.");
    return x;
}

std::string Value::toString() const
{
    std::ostringstream oss;
    if (this->getSimpleType() == SIMPLE_NUMERIC_VALUE)
        oss << this->getNumericValue();
    else if (this->getType() == STRING_VALUE)
        oss << this->getStringValue();
    else if (this->getType() == ARRAY_VALUE)
    {
        oss << "Array(" << std::endl;
        for (std::map<Value, Value>::const_iterator it = this->values.begin(); it != this->values.end(); it++)
            oss << "\t\"" << it->first.toString() << "\" => \"" << it->second.toString() << "\"" << std::endl;
        oss << ")";
    }
    return oss.str();
}

std::string Value::getTypeTitle() const
{
    std::string _r;
    switch (this->getType())
    {
    case INTEGRAL_VALUE:
        _r = "Int";
        break;
    case DOUBLE_VALUE:
        _r = "Double";
        break;
    case STRING_VALUE:
        _r = "String";
        break;
    case ARRAY_VALUE:
        _r = "Array";
        break;
    }
    return _r;
}