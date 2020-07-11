#include "radixtree.h"
#include <iostream>
#include <algorithm>
bool RadixTree::insert(const std::string &str)
{
    //TODO: Перевод строки а нижний регистр
//    std::transform(str.begin(), str.end(), str.begin(),
//                   [](auto ch){return std::tolower(ch);});
    //TODO: Проверка строки на наличие недопустимых символов

    const int aAscii = 97;

    auto *node = &root->child;
    auto itb = str.begin();
    auto ite = str.end();

    auto i = str[0] - aAscii; // 0 - 25
    while(1)
    {
        if(!(*node)[i]) // Сразу создаем новый нод
        {
            (*node)[i] = std::make_unique<Node>(std::string(itb, ite), true);
            return true;
        }

        auto pair = std::mismatch(itb, ite, (*node)[i]->label.begin());

        if(*pair.first == '\0' && *pair.second == '\0') { //Если слова/префиксы одинаковые
            if(!(*node)[i]->isEnd)
            {
                (*node)[i]->isEnd = true;
                return true;
            } else {
                 return false;
            }
        } else if(*pair.first != '\0' && *pair.second != '\0') { //Если совпадает только часть слова/префикса
            bool isCurrentNodeEnd = ((*node)[i]->isEnd) ? true : false;

            auto tmp = std::move((*node)[i].get()->child);
            (*node)[i]->child[*pair.first - aAscii] = std::make_unique<Node>(std::string(pair.first, ite), true);

            std::string tempStr(pair.second, (*node).at(i)->label.end());
            (*node)[i]->label = std::string((*node)[i]->label.begin(), pair.second);
            (*node)[i]->isEnd = false;

            //Вставка узла между 2-мя другими
            (*node)[i]->child[tempStr[0] - aAscii] = std::make_unique<Node>(tempStr, isCurrentNodeEnd);
            (*node)[i]->child[tempStr[0] - aAscii]->child = std::move(tmp);
            return true;
        } else if(*pair.first == '\0') { // Если node[i].label длиннее
        //Если старый префикс полностью содержится в новом слове/префиксе
            /*Тут записываем отличающийся префикс в временную строку*/
            std::string tempStr(pair.second, (*node).at(i)->label.end());
            itb = tempStr.begin();
            ite = tempStr.end();
            /*Тут записываем отличающийся префикс в временную строку*/

            //Перезаписываем старую строку на новую
            (*node)[i]->label = str;
            node = &node->at(i)->child;
            i = *itb - aAscii;
        } else if (*pair.second == '\0') { // Если str длинее
            //Если новое слово/префикс полностью содержится в старом префиксе
            itb = pair.first; // if(pair.first != ite) ???
            node = &node->at(i)->child;
            i = *pair.first - aAscii; // if(i >= 0 && i < 26) ???
        }
    }
    return false;
}

//void RadixTree::insert([[maybe_unused]]std::string &&str)
//{

//}

//bool RadixTree::Node::insert(const std::string &str)
//{

//}
