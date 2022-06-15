#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <algorithm>

using namespace std;


struct Node {

    size_t number_of_vertic = 0;
    vector<int> list_of_anjured_vertics;
    Node* next = nullptr;

    Node() = default;

};


class Graf {

private:
    Node* head = nullptr;
    static size_t count;


private:

    void add_vertic() {

        if (head == nullptr) {

            head = new Node();
            head->number_of_vertic = ++count;
            return;
        }

        Node* temp;
        temp = head;

        for (size_t i = 0; i < count - 1; i++) {

            temp = temp->next;
        }

        temp->next = new Node();
        temp->next->number_of_vertic = ++count;

    }

    void Print(ostream& str) const {
    
        Node* temp = head;
        while (temp) {

            str << temp->number_of_vertic << " ->  ";
            for (auto el : temp->list_of_anjured_vertics) {

                str << el << " ";
            }

            str << endl << "|" << endl;
            temp = temp->next;
        }
    }

    bool Search_sources(size_t Vertic, vector<short>& src, int n = 0, int k = 0) {
  
        src[Vertic - 1] = 1;

        Node* temp = head;
        for (size_t i = 0; i < Vertic - 1; i++)
        {
            temp = temp->next;
        }

        for (size_t i = 0; i < temp->list_of_anjured_vertics.size(); i++)
        {
            src[temp->list_of_anjured_vertics[i] - 1]++;
        }

        for (size_t i = 0; i < temp->list_of_anjured_vertics.size(); i++)
        {
            if (find(src.begin() + n, src.end() - k, n) == src.end() - k) {

                return true;
            }
            else if(src[temp->list_of_anjured_vertics[i] - 1] < 2) {

                Search_sources(temp->list_of_anjured_vertics[i], src);

            }
        }

        if (find(src.begin() + n, src.end() - k, 0) == src.end() - k) {

            return true;
        }

        return false;

    
    }


    bool Search_drains(size_t Vertic, vector<short>& src) {
        
        for (size_t i = 1; i <= count; i++)
        {
            if (i == Vertic)
                continue;

            if (!Search_sources(i, src, Vertic - 1, count - Vertic))
                return false;

            fill(src.begin(), src.end(), 0);
        }

        return true;
    }
        
public:

    Graf() = default;

    Graf(Graf& other) = delete;

    Graf& operator=(const Graf& other) = delete;
    
    void add_vertics(size_t Number_of_vertics) {

        for (size_t i = 0; i < Number_of_vertics; i++)
        {
            this->add_vertic();
        }
    }


    void add_edge(size_t Vertic, const size_t Number_of_vertic) {

        if (Vertic > count || Number_of_vertic == Vertic || Number_of_vertic > count)
        {
            throw invalid_argument("Invalid argument");
            return;
        }

        Node* temp = head;

        for (size_t i = 0; i < Vertic - 1; i++)
        {
            temp = temp->next;
        }
        if (find(temp->list_of_anjured_vertics.begin(), temp->list_of_anjured_vertics.end(), Number_of_vertic) == temp->list_of_anjured_vertics.end())
        {
            temp->list_of_anjured_vertics.push_back(Number_of_vertic);
        }

    }


    void add_edges(size_t Vertic, vector<int> Number_of_vertics) {
    
        for(auto el : Number_of_vertics)
        {
            add_edge(Vertic, el);
        }

    }


    void Task() {

        vector<bool> sources_vertic(count);
        vector<bool> drains_vertic(count);

        for (size_t i = 0; i < count; i++)
        {
            vector<short> src1(count);
            vector<short> src2(count);
            sources_vertic[i] = Search_sources(i + 1,src1);
            drains_vertic[i] = Search_drains(i + 1, src2);
        }


        cout << "Sources vertic: ";
        for (size_t i = 0; i < count; i++)
        {
            if (sources_vertic[i]) {

                cout << i + 1 << " ";
            }
        }

        cout << endl << endl;


        cout << "Drains vertic: ";
        for (size_t i = 0; i < count; i++)
        {
            if (drains_vertic[i]) {

                cout << i + 1 << " ";
            }
        }

        cout << endl << endl;
    
    }

    friend ostream& operator<<(ostream& str, const Graf& g) {
    
        g.Print(str);
        return str;
    
    }


};

size_t Graf::count = 0;


int main()
{

     Graf _graf;

     _graf.add_vertics(6);

     _graf.add_edges(2, { 1, 3, 4, 5});
     _graf.add_edges(4, { 6 });
     _graf.add_edges(1, { 6 });
     _graf.add_edges(3, { 1 });
     _graf.add_edges(5, { 3 });


     _graf.Task();

     return 0;

}