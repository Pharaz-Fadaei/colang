#include "syntax_tree/literal_block.h"
#include "utility.cpp"

LiteralBlock::LiteralBlock(Value value)
{
    this->value = value;
}

LiteralBlock::LiteralBlock(std::string *str, ValueType type)
{
    std::string *input;
    if(type == STRING_VALUE)
        input = new std::string(this->getEscapedString(*str));
    else
        input = str;

    this->value = Value(input, type);
}

std::string LiteralBlock::getEscapedString(const std::string& str) const
{
        std::ostringstream oss;
        int n = str.size();
        for(int i = 0; i < n; i++)
        {
            if(str[i] == '\\' && i != n - 1)
            {
                switch(str[i+1])
                {
                case 'n':
                    oss << '\n';
                    break;
                case 'r':
                    oss << '\r';
                    break;
                case 't':
                    oss << '\t';
                    break;
                case '\\':
                    oss << '\\';
                    break;
                case '"':
                    oss << '\"';
                    break;
                default:
                    Utility::error("Unknown escape character requested!");
                }
                i++;
            }
            else
                oss << str[i];
        }
        return oss.str();
}


Value LiteralBlock::Run(Scope *scope)
{
    return this->value;
}
std::string LiteralBlock::typeName()
{
    return "LiteralBlock";
}
