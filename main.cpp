#include <iostream>

using namespace std;

class Main_stack
{
protected:
    struct element
    {
        element *prev;
        int x;
    };
    element *top;
public:
    Main_stack ()
    {
        top = NULL;
    }

    ~Main_stack ()
    {
        while ((top != NULL))
        {
            element *temp;
            temp = top;
            top = top->prev;
            delete temp;
        }
        delete top;
    }

    void push(int);
    void pop();
    int top_el();
    bool is_empty();
};

class C_stack : public Main_stack
{
public:
    C_stack () : Main_stack()
    {
    }

    void swap_stacks(C_stack*,C_stack*, int num);
    void Print();
    int Number_Of_Elements();
    void Add_To_Center(int);
    void Add_After(int,int);
    void sort(C_stack*,C_stack*);
    void EDS();
    void SHELL();
    int Get_X(int);
    void Swap(C_stack*, int num_a, int num_b);
    void Insertion();
    int Min();
    int Max();
    void CountingSort();
    void BinSort();
};

void Main_stack ::push(int el)
{
    element *temp = new element;
    temp->x = el;
    temp->prev = top;
    top = temp;
}

int Main_stack ::top_el()
{
    if (this->top)
        return top->x;
}

void Main_stack :: pop()
{
    if (top != NULL)
    {
        element *temp;
        temp = top;
        top = top->prev;
        delete temp;
    }
}

bool Main_stack::is_empty()
{
    if (top != NULL)
        return 0;
    else return 1;
}

void C_stack ::swap_stacks(C_stack* s1, C_stack *s2, int num)
{
    if (num)
    {
        for (int i(0); i < num; i++)
        {
            s2->push(s1->top_el());
            s1->pop();
        }
    }
}

void C_stack ::Print()
{
    C_stack *temp = new C_stack;
    temp->top = NULL;
    int count(0);
    while (top != NULL)
    {
        cout << top_el() << endl;
        swap_stacks(this,temp,1);
        count ++;
    }
    swap_stacks(temp,this,count);
    delete temp;
}

int C_stack :: Number_Of_Elements()
{
    if (!is_empty())
    {
        C_stack *temp = new C_stack; //= NULL;
        int count (0);
        while (top != NULL)
        {
            swap_stacks(this,temp,1);
            count++;
        }
        swap_stacks(temp,this,count);
        delete temp;
        return count;
    }
    else return 0;
}

void C_stack ::Add_To_Center(int x)
{
    int count(1);
    int Number = Number_Of_Elements();
    while ((count != Number) || (abs(count - Number) != 1))
    {
        count ++;
        Number --;
    }
    C_stack *temp = new C_stack;
    swap_stacks(this,temp,count);
    push(x);
    swap_stacks(temp,this,count);
    delete temp;
}

void C_stack ::Add_After(int x, int pos)
{
    int Number = Number_Of_Elements();
    C_stack *temp = new C_stack;
    if ((!is_empty()) && (Number >= pos))
    {
        swap_stacks(this,temp,(Number-pos));
        push(x);
        swap_stacks(temp,this,(Number-pos));
    }
    delete temp;
}

void C_stack ::sort(C_stack* s1,C_stack* s2)
{
    C_stack *temp = new C_stack;
    while ((s2->top != NULL) && (s1->top != NULL))
    {
        if (s1->top_el() >= s2->top_el())
        {
            swap_stacks(s1,temp,1);
        }
        else
            swap_stacks(s2,temp,1);
    }

    if (s1->top != NULL)
        swap_stacks(s1,temp,s1->Number_Of_Elements());
    else if (s2->top != NULL)
        swap_stacks(s2,temp,s2->Number_Of_Elements());

    swap_stacks(temp,s1,temp->Number_Of_Elements());

    delete temp;
}

void C_stack ::EDS()
{
    C_stack *s2 = new C_stack;
    C_stack *buf = new C_stack;

    swap_stacks(this,s2,Number_Of_Elements()-1);
    while ((this->top_el() <= s2->top_el()) && (s2->top != NULL))
        swap_stacks(s2,this,1);

    swap_stacks(s2,buf,s2->Number_Of_Elements()-1);
    while ((s2->top_el() <= buf->top_el()) && (buf->top != NULL))
        swap_stacks(buf,s2,1);

    if (buf->Number_Of_Elements() > 2)
        buf->EDS();

    sort(this,s2);
    sort(this,buf);

    delete s2;
    delete buf;
}

int C_stack ::Get_X(int num)
{
    int x = 0; int col = Number_Of_Elements()-num;
    C_stack *temp = new C_stack;
    swap_stacks(this,temp,col);
    x = top_el();
    swap_stacks(temp,this,col);
    delete temp;
    return x;
}

void C_stack ::Swap(C_stack *a, int numa, int numb)
{
    C_stack *tempa = new C_stack;
    C_stack *tempb = new C_stack;

    swap_stacks(a,tempb,a->Number_Of_Elements()-numb+1);
    swap_stacks(a,tempa,a->Number_Of_Elements()-numa+1);
    swap_stacks(tempb,a,1);
    swap_stacks(tempa,tempb,1);
    swap_stacks(tempa,a,tempa->Number_Of_Elements());
    swap_stacks(tempb,a,tempb->Number_Of_Elements());

    delete tempa;
    delete tempb;
}

void C_stack ::SHELL()
{
    int n = Number_Of_Elements();
    for (int incr = n/2; incr > 0; incr/=2) {
        for (int i = incr+1; i <= n; i++) {
            for (int j = i - incr; j > 0; j-=incr) {
                if(this->Get_X(j) > this->Get_X(j + incr))
                    this->Swap(this,j,j + incr);
                else j = 0;
            }
        }
    }
}

void C_stack ::Insertion()
{
    for (int i = 2; i <= Number_Of_Elements(); i++)
    {
        int j = i;
        while (this->Get_X(j) < this->Get_X(j-1)) {
            Swap(this,j-1,j);
            j = j - 1;
            if (j <2)
                break;
        }
    }
}

int C_stack ::Min()
{
    int min = top_el();
    C_stack *temp = new C_stack;
    while (!is_empty()) {
        swap_stacks(this,temp,1);
        if (min > top_el())
            min = top_el();
    }
    swap_stacks(temp,this,temp->Number_Of_Elements());
    delete temp;
    return min;
}

int C_stack ::Max()
{
    int max = top_el();
    C_stack *temp = new C_stack;
    while (!is_empty()) {
        swap_stacks(this,temp,1);
        if (max < top_el())
            max = top_el();
    }
    swap_stacks(temp,this,temp->Number_Of_Elements());
    delete temp;
    return max;
}

void C_stack ::CountingSort()
{
    int min = Min();
    int max = Max();

    int *array = new int[max-min+1];

    C_stack *temp = new C_stack;
    swap_stacks(this,temp,Number_Of_Elements());

    for (int i = min; i <= max; i++)
        array[i-min] = 0;

    while (!temp->is_empty()) {
        array[temp->top_el()] ++;
        temp->pop();
    }

    for (int i = min; i <= max; i++) {
        for (int j = 0; j < array[i-min]; j++) {
            this->push(i);
        }
    }

    delete array;
    delete temp;
}

void push_and_sort_stack(C_stack &stack)
{
	int temp;

	while (scanf("%d", &temp) != -1)
	{
		stack.push(temp);
	}
	stack.Insertion();
	stack.Print();
}


int main()
{
    C_stack a;
    push_and_sort_stack(a);
    return 0;
}
