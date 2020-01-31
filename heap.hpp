#ifndef HEAP_HPP
#define HEAP_HPP

struct Dist
{
    /* A structure use to holds Centroid's ID and a newly calculated euclidean distance */
    int num;
    double distance;
};

class Heap
{
    /* Min Heap */
    private:  
        struct Node  
        {
            /* Node structure for heap */
            Dist* item;
            Node* next;
            Node* prev;
        };

        Node* head;             //declare head
        Node* bottom;           //declare bottom
        int size = 0;           //declare size

    public:     
        Heap()  
        {
            //initalizes head and bottom
            head = new Node();
            bottom = new Node();
        }

        Dist* pop()
        {
            if (size == 1)
            {
                //return head if size is 1
                Dist* target = new Dist();
                target = head->item;
                head->item = nullptr;
                size --;
                return target;
            }
            else if (size == 2)
            {
                //if return bottom if size is 2
                Dist* target = new Dist(); 
                target = bottom->item;
                bottom->item = nullptr;
                size --;
                return target;
            }
            else if (size > 2)
            {
                //pop bottom and set it to equal its previous
                Dist* target = new Dist(); 
                target = bottom->item;
                bottom->item = bottom->prev->item;
                Node* prev = bottom->prev->prev;
                free(bottom->prev);         //free previous node of bottom since bottom holds the previous node's item
                prev->next = bottom;
                bottom->prev = prev;
                size --;
                return target;
            }
            else 
            {
                //size == 0
                cout << "\nHeap is EMPTY!" << endl;
            }
        }

        void insert(Dist* target)
        {
            if (size == 0)
            {
                //set head when heap is empty
                head->item = target;
                head->prev = nullptr;
                bottom->next = nullptr;
                size ++;
            }

            else if (size == 1)
            {
                //when heap is size 1
                if (head->item->distance >= target->distance)
                {
                    //set bottom if target is less than head
                    bottom->item = target;
                }
                else
                {
                    //if target is more than head, set head = target and bottom = old head
                    bottom->item = head->item;
                    head->item = target;
                }
                //link head and bottom
                bottom->prev = head;
                head->next = bottom;
                size ++;
            }    
            else 
            {
                if (head->item->distance <= target->distance)
                {
                    //set new head if target > head
                    Node* old_head = new Node();
                    old_head->item = head->item; old_head->next = head->next;
                    head->next->prev = old_head; old_head->prev = head;
                    head->item = target; head->next = old_head;
                }
                else if (bottom->item->distance >= target->distance)
                {
                    //set new bottom if bottom > target
                    Node* old_bot = new Node();
                    old_bot->item = bottom->item; old_bot->prev = bottom->prev;
                    bottom->prev->next = old_bot; old_bot->next = bottom;
                    bottom->item = target; bottom->prev = old_bot;
                }
                else  
                {
                    //find a node that is less than target
                    Node* current = head;
                    while (current->next != nullptr && current->item->distance > target->distance)
                    {
                        current = current->next;
                    }
                    //set new node in between current and current->prev
                    Node* entry = new Node();
                    entry->item = target; 
                    entry->next = current; current->prev->next = entry; 
                    entry->prev = current->prev; current->prev = entry;
                }
                //increment size
                size ++;
            }

        }
};

#endif