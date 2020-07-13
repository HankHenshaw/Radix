#include "radixtree.h"
#include <iostream>
#include <algorithm>
#include <stack>

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

    auto i = str[0] - aAscii;
    while(1)
    {
        if(!(*node)[i]) // Сразу создаем новый нод
        {
            (*node)[i] = std::make_shared<Node>(std::string(itb, ite), true);
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
            (*node)[i]->child[*pair.first - aAscii] = std::make_shared<Node>(std::string(pair.first, ite), true);


            std::string tempStr(pair.second, (*node).at(i)->label.end());
            (*node)[i]->label = std::string((*node)[i]->label.begin(), pair.second);
            (*node)[i]->isEnd = false;

            //Вставка узла между 2-мя другими
            (*node)[i]->child[tempStr[0] - aAscii] = std::make_shared<Node>(tempStr, isCurrentNodeEnd);

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
            itb = pair.first;
            node = &node->at(i)->child;
            i = *pair.first - aAscii;
        }
    }
    return false;
}

void RadixTree::print() const
{
    std::stack<Node*> stackOfNodes;
    std::stack<int> stackOfSpaces;

    stackOfNodes.push(root);
    stackOfSpaces.push(0);

    while(!stackOfNodes.empty())
    {
        auto node = stackOfNodes.top();
        auto spaces = stackOfSpaces.top();
        stackOfNodes.pop();
        stackOfSpaces.pop();

        for(auto i = 0; i < spaces; ++i)
        {
            std::cout << ' ';
        }

        auto newSpaces = ++spaces;
        if(node->isEnd)
            std::cout << node->label << '$' << '\n';
        else
            std::cout << node->label << '\n';

        for(size_t i = 0; i < node->child.size(); ++i)
        {
            if(node->child[i])
            {
                stackOfNodes.push(node->child[i].get());
                stackOfSpaces.push(newSpaces);
            }
        }
    }
}

bool RadixTree::find(const std::string &str)
{
    const int aAscii = 97;

    if(str.empty())
        return false;

    auto node = root->child;

    if(!node[str[0] - aAscii])
        return false;

    auto itb = str.begin();

    while(1)
    {
        auto pair = std::mismatch(node[*itb - aAscii]->label.begin(),
                                  node[*itb - aAscii]->label.end(),
                                  itb);

        if(*pair.first == '\0' && *pair.second == '\0')
        {
            if(node[*itb - aAscii]->isEnd)
                return true;
            else
                return false;
        } else if(*pair.second == '\0') {
            return false;
        } else if(std::string(pair.second, str.end()) == std::string(itb, str.end()))
            return false;

        node = node[*itb - aAscii]->child;
        itb = pair.second;

        if(!node[*itb - aAscii])
            return false;
    }

    return false;
}

/*
void RadixTree::remove(const std::string &str)
{
    if(!find(str))
        return;

    const int aAscii = 97;

    auto node = root->child[str[0] - aAscii];
    auto prevNode = std::make_shared<Node>(Node());

    auto itb = str.begin();

    while(1)
    {
        auto pair = std::mismatch(node->label.begin(),
                                  node->label.end(),
                                  itb);

        if(*pair.first == '\0' && *pair.second == '\0')
        {
            int counterOfChilds = 0;
            int counterOfSiblings = -1; // -1 - т.к. 1 мы получим за себя
            for(size_t i = 0; i < Node::SIZE; ++i)
            {
                if(node->child[i])
                {
                    if(!node->child[i]->label.empty())
                        ++counterOfChilds;
                }

                if(prevNode->child[i])
                {
                    if(!prevNode->label.empty()) //Проверка для корня
                    {
                        if(!prevNode->child[i]->label.empty())
                        {
                            ++counterOfSiblings;
                        }
                    }
                }
            }

            if(counterOfChilds)
            {
                node->isEnd = false;
                std::cout << "Delete No. 1\n";
                return;
            }

            if(counterOfSiblings == 1)
            {
                prevNode->label += node->label;
                node->label.clear();
                node->isEnd = false;
                std::cout << "Delete No. 2\n";
                return;
            } else {
                node->label.clear();
                node->isEnd = false;
                std::cout << "Delete No. 3\n";
                return;
            }
        }

        prevNode = node;
        itb = pair.second;
        node = node->child[*itb - aAscii];
    }
    //3 Возможных сценария:
    //1 - Если узел не конечный и у него стоит признак, что он конечный, то
    //просто меняем признак на 0
    //2 - Если узел конечный, но от этого префикса остался еще 1 узел, то
    //надо удалить узел который мы хотели удалить, а префикс от
    //предыдущего узла совместить с отставшимся префиксом
    //3 - Если не осталось от предыдущего префикса больше префиксов или
    //их больше 1, то просто удаляем узел
}
*/