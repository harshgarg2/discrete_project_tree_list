#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class info
{
public:
    string name;
    int salary;
    int age;
};

class linked_list_node
{
public:
    info data;
    linked_list_node *next;
    linked_list_node()
    {
        cout << "Enter the name of Employee: ";
        cin >> data.name;
        cout << "Enter the salary of employee: ";
        cin >> data.salary;
        cout << "Enter the age of employee: ";
        cin >> data.age;
        cout << endl;
    }
};

linked_list_node *create_linked_list(int n)
{
    linked_list_node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        linked_list_node *n = new linked_list_node;
        n->next = head;
        head = n;
    }
    return head;
}
class abstract
{
public:
    int size_of_linked_list(linked_list_node *root)
    {
        int n = 0;
        while (root)
        {
            n++;
            root = root->next;
        }
        return n;
    }
};
class tree_node : public abstract
{

    public:
    string post_name;
    int total_no_of_seats;
    int no_of_person;
    linked_list_node *head;
    vector<tree_node *> children;

    tree_node()
    {
        cout << " Enter the post_name: ";
        cin >> post_name;
        cout << endl
             << "Enter numbers of seats for this Post: ";
        cin >> total_no_of_seats;
        cout << "Enter number of members in this post: ";
        cin >> no_of_person;
        head = create_linked_list(no_of_person);
    }
};

class tree_list : public abstract
{
    string company_name;
    tree_node *company_root;

public:
    tree_list()
    {
        cout << endl
             << "Welcome to new Company" << endl;
        cout << endl
             << "Enter the name of Company: ";
        cin >> company_name;
        cout << endl
             << "Enter the details of company..." << endl
             << endl;
        company_root = take_input_level_wise();
    }

    // Taking Input at one time level wise

    tree_node *take_input_level_wise()
    {
        tree_node *root = new tree_node();
        queue<tree_node *> pending_nodes;

        pending_nodes.push(root);
        while (pending_nodes.size())
        {
            tree_node *front = pending_nodes.front();
            pending_nodes.pop();
            cout << endl
                 << "Enter the number of successor post of " << front->post_name << ": ";
            int num_of_post;
            cin >> num_of_post;
            for (int i = 1; i < num_of_post + 1; i++)
            {
                cout << endl
                     << "Enter " << i << "th successor post of " << front->post_name << endl;
                tree_node *child = new tree_node();
                front->children.push_back(child);
                pending_nodes.push(child);
            }
        }
        return root;
    }

    // printing all the posts of company/ data of company

    void printLL(linked_list_node *head)
    {

        while (head != NULL)
        {
            cout << "EMPLOYEE NAME  : " << head->data.name << endl;
            cout << "EMPLOYEE SALARY: " << head->data.salary << endl;
            cout << "EMPLOYEE AGE   : " << head->data.age << endl;
            head = head->next;
            cout << endl;
        }
        cout << endl;
    }

    void print_level_wise()
    {
        cout << endl
             << "Press Enter to display the Company data....";
        cin.get();
        cin.get();
        cout << endl
             << "Whole Data of Company " << company_name << " is..." << endl
             << endl;

        tree_node *root = company_root;
        if (root == NULL)
        {
            return;
        }
        queue<tree_node *> pendingnodes;
        pendingnodes.push(root);
        while (pendingnodes.size())
        {
            tree_node *front = pendingnodes.front();
            cout << "The " << front->post_name << " have " << size_of_linked_list(front->head) << " employees and their details are given below:" << endl;
            printLL(front->head);
            pendingnodes.pop();

            for (int i = 0; i < front->children.size(); i++)
            {
                pendingnodes.push(front->children[i]);
            }
            cout << endl;
        }
        cout << endl
             << "Enter to continue....";
        cin.get();
    }

    // Searching for post and person/ employee data

    tree_node *search_post(tree_node *root, string post)
    {
        if (!root)
            return NULL;

        if (post == root->post_name)
            return root;
        else
            for (int i = 0; i < root->children.size(); i++)
            {
                tree_node *temp = search_post(root->children[i], post);
                if (temp)
                    return temp;
            }
        return NULL;
    }

    info *search_person(linked_list_node *temp, string name)
    {
        if (!temp)
            return NULL;
        if (name == temp->data.name)
            return &temp->data;
        else
            return search_person(temp->next, name);
    }
    void print_person_data(info *info_temp)
    {
        cout << endl
             << "Employee details are: " << endl;
        cout << "EMPLOYEE NAME  : " << info_temp->name << endl;
        cout << "EMPLOYEE SALARY: " << info_temp->salary << endl;
        cout << "EMPLOYEE AGE   : " << info_temp->age << endl;
    }

    void print_post_person()
    {
        string name, post;
        cout << endl
             << "Enter the name of Employee: ";
        cin >> name;
        cout << endl
             << "Enter the Post Name: ";
        cin >> post;
        tree_node *root = company_root;
        tree_node *extra = search_post(root, post);
        if (extra)
        {
            linked_list_node *temp = extra->head;
            info *info_temp = search_person(temp, name);
            if (info_temp)
                print_person_data(info_temp);
            else
                cout << endl
                     << "No person of this Credential Exits in Company...";
        }
        else
        {
            cout << endl
                 << "No person of this Credential Exits in Company...";
        }
        cout << endl
             << "Press enter to continue.....";
        cin.get();
    }

    void total_vacancy_helper(tree_node *root, queue<tree_node *> &q)
    {
        if (!(q.size()))
            return;
        cout << endl
             << "Vacancy of post " << q.front()->post_name << " is: " << q.front()->total_no_of_seats - q.front()->no_of_person;
        for (int i = 0; i < q.front()->children.size(); i++)
            q.push(q.front()->children[i]);
        q.pop();
        total_vacancy_helper(q.front(), q);
    }

    void total_vacancy()
    {
        queue<tree_node *> q;
        q.push(company_root);
        cout << endl
             << "Total Post in " << company_name << " are as follow:";
        total_vacancy_helper(company_root, q);
        cin.get();
        cout << endl
             << "Enter to continue.....";
        cin.get();
    }

    void vacancy_by_post_helper(string s, tree_node *temp)
    {
        if (!temp)
            return;

        if (temp->post_name == s)
            cout << temp->post_name << " vacancy :" << temp->total_no_of_seats - temp->no_of_person << endl;

        for (int i = 0; i < temp->children.size(); i++)
            vacancy_by_post_helper(s, temp->children[i]);
    }
    void vacancy_by_post()
    {
        cout << endl;
        system("clear");
        string s;
        cout << "ENTER THE POST FOR WHICH YOU WOULD LIKE TO SEE THE VACANCY: ";
        cin >> s;
        cout << endl;
        vacancy_by_post_helper(s, company_root);
        cin.get();
        cout << endl
             << "Enter to continue.....";
        cin.get();
    }

    void vacancy()
    {
        // Menu for vacancy
        cout << endl;
        system("clear");
        cout << endl
             << "Choose type of Vacancy search : ";
        cout << endl;
        int n;
        cout << endl
             << "1. Total Vacancies in Company";
        cout << endl
             << "2. Vacancies by Post Name";
        cout << endl
             << endl
             << "Choice (1/2): ";
        cin >> n;
        switch (n)
        {
        case 1:
            total_vacancy();
            break;
        case 2:
            vacancy_by_post();
            break;
        default:
            cout << endl
                 << "Please enter a valid no. next time";
            cout << endl
                 << "Enter to continue....";
            cin.get();
            break;
        }
    }

    void update_linked_list_from_inserting(tree_node *temp)
    {
        if (temp->total_no_of_seats == temp->no_of_person)
        {
            cout << "WE ARE SORRY BUT THE VACANCIES ARE ALREADY FILLED FOR THIS POST" << endl;
            return;
        }
        linked_list_node *N = new linked_list_node();
        temp->no_of_person++;
        N->next = temp->head;
        temp->head = N;
        cout << endl;
    }
    void insert_employee()
    {
        string P_post;
        cout << "ENTER THE POST WHERE AN EMPLOYEE IS TO BE ADDED" << endl;
        cin >> P_post;
        cout << endl;
        queue<tree_node *> pendingnodes;
        tree_node *temp = company_root;
        pendingnodes.push(temp);

        while (pendingnodes.size())
        {
            if (temp->post_name == P_post)
            {
                update_linked_list_from_inserting(temp);
                return;
            }
            for (int i = 0; i < temp->children.size(); i++)
            {
                pendingnodes.push(temp->children[i]);
            }
            pendingnodes.pop();
            temp = pendingnodes.front();
        }
    }
    void insert_post()
    {
        string P_post;
        cout << "ENTER THE PREVIOUS POST AFTER WHICH NEW POST IS TO BE STARTED" << endl;
        cin >> P_post;
        cout << endl;
        queue<tree_node *> pendingnodes;
        tree_node *temp = company_root;
        pendingnodes.push(temp);
        tree_node *N = new tree_node();

        while (pendingnodes.size())
        {
            if (temp->post_name == P_post)
            {
                temp->children.push_back(N);
                return;
            }
            for (int i = 0; i < temp->children.size(); i++)
            {
                pendingnodes.push(temp->children[i]);
            }
            pendingnodes.pop();
            temp = pendingnodes.front();
        }
    }

    info *delete_employee_helper(linked_list_node *temp, linked_list_node *temp_prev, string name)
    {
        if (!temp)
            return NULL;
        if (name == temp->data.name)
        {
            temp_prev->next = temp->next;
            return &temp->data;
        }
        else
        {
            temp_prev = temp;
            return delete_employee_helper(temp->next, temp_prev, name);
        }
    }

    void delete_employee()
    {
        string name, post;
        cout << endl
             << "Enter the name of Employee: ";
        cin >> name;
        cout << endl
             << "Enter the Post Name: ";
        cin >> post;
        tree_node *extra = search_post(company_root, post);
        linked_list_node *temp = extra->head;
        if (temp)
        {
            int e = size_of_linked_list(temp);
            info *info_temp = delete_employee_helper(temp, temp, name);
            if (info_temp)
            {
                if (e == 1)
                    extra->head = NULL;
                print_person_data(info_temp);
                cout << endl
                     << "Employee with above credential has been deleted";
            }
        }
        else
        {
            cout << endl
                 << "No post of this Credential Exits in Company...";
        }
        cout << endl
             << "Press enter to continue.....";
        cin.get();
    }
};

int main()
{
    tree_list obj;
    while (1)
    {
        cout << endl;
        cin.get();
        system("clear");
        int n;
        cout << endl
             << endl
             << "1. Print level Wise";
        cout << endl
             << "2. Delete Employee";
        cout << endl
             << "3. Vacancy";
        cout << endl
             << "4. Print Data of Employee";
        cout << endl
             << "5. Insert Post";
        cout << endl
             << "6. Insert Employee";
        cout << endl
             << "7. Exit";
        cout << endl
             << endl
             << "Choose an option : ";

        cin >> n;
        switch (n)
        {
        case 1:
            obj.print_level_wise();
            break;
        case 2:
            obj.delete_employee();
            break;
        case 3:
            obj.vacancy();
            break;
        case 4:
            obj.print_post_person();
            break;
        case 5:
            obj.insert_post();
            break;
        case 6:
            obj.insert_employee();
            break;
        case 7:
            exit(0);
            break;

        default:
            break;
        }
    }
    return 0;
}
