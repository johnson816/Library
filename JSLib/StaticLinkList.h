#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace JSLib
{

template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    struct SNode : public Node
    {
        void* operator new(unsigned int size,void* local)
        {
            (void) size;
            return local;
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];

    Node* creat()
    {
        SNode* ret = NULL;
        for(int i=0;i<N;i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }

    void destroy(Node* pn)
    {
        SNode* tem = reinterpret_cast<SNode*>(m_space);
        SNode* pd = dynamic_cast<SNode*>(pn);
        for(int i=0;i<N;i++)
        {
            if(pd == (tem + i))
            {
                m_used[i] = 0;
                pd->~SNode();
                break;
            }
        }
    }
public:
    StaticLinkList()
    {
        for(int i=0;i<N;i++)
        {
            m_used[i] = 0;
        }
    }
    int capacity()
    {
        return N;
    }
    ~StaticLinkList()
    {
        this->clear();
    }
};

}



#endif // STATICLINKLIST_H
