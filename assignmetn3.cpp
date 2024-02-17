#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <sstream>
using namespace std;

class LinkedList
{
public:
    struct File
    {
        int version;
        vector<string> contents;
        size_t hash_num;
        File *next;
    };

    File *head; //= nullptr;

    File *get_last_node(File *temp)
    {
        if (temp == nullptr)
        {
            return temp; // empty list
        }
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        return temp;
    }

    // public:
    LinkedList() : head(nullptr) {}

    // explicit LinkedList(File *head) : head(head) {}

    ~LinkedList()
    {
        File *current = head;
        while (current != nullptr)
        {
            File *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class Git322
{
    friend class EnhancedGit322;
private:
    // friend class LinkedList;
    
    LinkedList mylist;
    int num_version; // = 1;
    string filename; // = "file.txt";

    size_t hash_it(string content)
    {
        hash<string> hash_obj;
        return hash_obj(content);
    }

    // return the last node of the linked list

public:
    Git322(int num_version, string filename) : mylist(),
                                               num_version(num_version),
                                               filename(filename)
    {
    }
    ~Git322()
    {
    }

    void helpdesk()
    {
        cout << "To add the content of your file to version control press 'a'\n";
        cout << "To remove a version press 'r'\n";
        cout << "To load a version press 'l'\n";
        cout << "To print to the screen the detailed list of all versions press 'p'\n";
        cout << "To compare any 2 versions precc 'c'\n";
        cout << "To search versions for a keyword press 's'\n";
        cout << "To exit press 'e'\n";
    }

    void add()
    {
        string content;
        string temp;
        ifstream f(filename);
        LinkedList::File *current = new LinkedList::File;
        size_t hash_num;
        // check if file valid
        if (!f.is_open())
        {
            cout << "Unable to open file." << endl;
            exit(1);
        }

        // all the file contents is stored in a string
        while (getline(f, temp))
        {
            content += temp;
            content += "\n";
        }

        f.close();
        hash_num = hash_it(content);
        current->contents.push_back(content);
        current->hash_num = hash_num;

        // if no file added yet
        if (mylist.head == nullptr)
        {
            current->version = num_version;
            mylist.head = current;
            current->next = nullptr;
            num_version++;
            cout << "Your content has been added successfully." << endl;
        }

        // append the new version to the end of the linked list
        else
        {
            LinkedList::File *newNode = mylist.get_last_node(mylist.head);
            if (newNode->contents == current->contents)
            {
                cout << "git322 did not detect any change to your file and will not create a new version." << endl;
            }
            else
            {
                newNode->next = current;
                current->version = ++newNode->version;
                num_version++;
                cout << "Your content has been added successfully." << endl;
            }
        }
    }

    // traverse the linked list and print
    void print(void)
    {
        if (mylist.head != nullptr)
        {
            LinkedList::File *current = mylist.head;
            cout << "Number of versions: " << num_version - 1 << endl;

            while (current != nullptr)
            {
                string contents;
                cout << "Version number: " << current->version << endl;
                cout << "Hash value: " << current->hash_num << endl;
                for (string line : current->contents)
                {
                    contents += line;
                    contents += "\n";
                }
                cout << "Content: " << contents << endl;
                current = current->next;
            }
        }
        else
        {
            cout << "Error: No file added\n";
        }
    }

    void load(int version)
    {
        // check version number if exceeding the range needed!!
        LinkedList::File *current = mylist.head;
        if (version < 1 || version > num_version - 1)
        {
            cout << "invalid version" << endl;
        }
        while (current != nullptr)
        {
            string contents;
            if (current->version == version)
            {
                ofstream fp(filename, ios::out | ios::trunc);
                if (fp.is_open())
                {
                    for (string line : current->contents)
                    {
                        contents += line;
                        contents += "\n";
                    }
                    fp << contents;
                    fp.close();
                    cout << "Version" << version << " loaded successfully. Please refresh your text editor to see the changes." << endl;
                }
                else
                {
                    cout << "File open error";
                }
            }
            current = current->next;
        }
    }

    // compare the content of two versions
    void compare(int version1, int version2)
    {
        LinkedList::File *current1 = mylist.head;
        LinkedList::File *current2 = mylist.head;
        vector<string> content1;
        vector<string> content2;
        while (current1 != nullptr && current1->version != version1)
        {
            current1 = current1->next;
        }
        while (current2 != nullptr && current2->version != version2)
        {
            current2 = current2->next;
        }
        if (current1 == nullptr || current2 == nullptr)
        {
            cout << "Please enter valid version numbers." << endl;
            return;
        }
        content1 = current1->contents;
        content2 = current2->contents;
        if (content1.size() == content2.size())
        {
            size_t min_size = min(content1.size(), content2.size());
            for (size_t i = 0; i < min_size; i++)
            {
                if (hash_it(content1[i]) != hash_it(content2[i]))
                {
                    cout << "Line" << i << ": " << content1[i] << "<<>>" << content2[i] << endl;
                }
                else if (hash_it(content1[i]) == hash_it(content2[i]))
                {
                    cout << "Line" << i + 1 << ": "
                         << "<Identical>" << endl;
                }
            }
        }
        else
        {
            size_t min_size = min(content1.size(), content2.size());

            for (size_t i = 0; i < min_size; i++)
            {
                if (hash_it(content1[i]) != hash_it(content2[i]))
                {
                    cout << "Line" << i + 1 << ": " << content1[i] << "<<>>" << content2[i] << endl;
                }
                else if (hash_it(content1[i]) == hash_it(content2[i]))
                {
                    cout << "Line" << i + 1 << ": "
                         << "<Identical>" << endl;
                }
            }

            if (content2.size() == min_size)
            {
                for (int i = min_size; i < content1.size(); i++)
                {
                    cout << "Line" << i + 1 << ": " << content1[i] << "<<>>"
                         << "<Empty line>" << endl;
                }
            }
            else if (content1.size() == min_size)
            {
                for (int i = min_size; i < content2.size(); i++)
                {
                    cout << "Line" << i + 1 << ": "
                         << "<Empty line>"
                         << "<<>>" << content2[i] << endl;
                }
            }
        }
    }

    // 检查所有的cout格式是否正确 空格
    // 检查所有的linked list current->contents名称是否正确
    void search(string keyword)
    {
        LinkedList::File *current = mylist.head;
        vector<string> content1;
        string temp;
        int success = 0;
        while (current != nullptr)
        {
            for (string content : current->contents)
            {
                if (content.find(keyword) != string::npos)
                {
                    cout << "The keyword '" << keyword << "' has been found in the following version:" << endl;
                    cout << "Version number: " << current->version << endl;
                    cout << "Hash value: " << current->hash_num << endl;
                    cout << "Content: ";
                    for (string line : current->contents)
                    {
                        cout << line << endl;
                    }
                    success++;
                    break;
                }
            }
            current = current->next;
        }
        if (success == 0)
        {
            cout << "Your keyword '" << keyword << "' was not found in any version." << endl;
        }
    }

    void remove(int version)
    {
        LinkedList::File *current = mylist.head;
        LinkedList::File *prev = nullptr;
        if (mylist.head == nullptr)
        {
            cout << "Error: No file added\n"
                 << endl;
            return;
        }
        // head node is the version to be removed
        if (mylist.head->version == version)
        {
            LinkedList::File *temp = mylist.head;
            mylist.head = mylist.head->next;
            delete temp;
            num_version--;
            cout << "Version " << version << " deleted successfully.\n";
            return;
        }

        if (current != nullptr && current->version == version)
        {
            mylist.head = current->next;
            delete current;
            cout << "Version " << version << " deleted successfully." << endl;
        }
        while (current != nullptr && current->version != version)
        {
            prev = current;
            current = current->next;
        }
        if (current == nullptr)
        {
            // didn't find
            cout << "Please enter a valid version number\n"
                 << endl;
            return;
        }
        prev->next = current->next;
        delete current;
        num_version--;
        cout << "Version " << version << "deleted successfully." << endl;
    }

    int get_num_version() const {
        return num_version;
    }
};

class EnhancedGit322 : public Git322
{
private:
    string versions_filename;

    // Save all versions to a file
    void save_versions()
    {
        ofstream f(versions_filename, ios::out | ios::trunc);
        if (f.is_open())
        {
            for (LinkedList::File *current = mylist.head; current != nullptr; current = current->next)
            {
                f << current->version << '\n';
                f << current->hash_num << '\n';
                for (string line : current->contents)
                {
                    f << line << '\n';
                }
                f << "---\n";
            }
            f.close();
        }
        else
        {
            cout << "Error: Unable to save versions to file " << versions_filename << endl;
        }
    }

    // Load all versions from a file
    void load_versions()
    {
        ifstream f(versions_filename);
        if (f.is_open())
        {
            LinkedList::File *current = nullptr;
            string line;
            while (getline(f, line))
            {
                if (line.empty() || line == "---")
                {
                    continue;
                }
                if (line == "version")
                {
                    int version;
                    getline(f, line);
                    version = stoi(line);
                    current = new LinkedList::File;
                    current->version = version;
                    getline(f, line);
                    current->hash_num = stoull(line);
                    mylist.head = current;
                }
                else if (current != nullptr)
                {
                    current->contents.push_back(line);
                }
            }
            f.close();
        }
        else
        {
            cout << "Error: Unable to load versions from file " << versions_filename << endl;
        }
    }

public:
    EnhancedGit322(int num_version, string filename, string versions_filename) : Git322(num_version, filename),
                                                                                 versions_filename(versions_filename)
    {
        load_versions();
    }

    ~EnhancedGit322()
    {
        save_versions();
    }

    void helpdesk()
    {
        Git322::helpdesk(); // Call the helpdesk function from the base class
    }
};

int main()
{
    string filename = "file.txt";
    string versions_filename = "versions.txt";
    EnhancedGit322 git(1, filename, versions_filename);
    // Git322 git(nullptr, 1, filename);
    string x;
    cout << "Welcome to the Comp322 file versioning system!\n"
         << endl;
    git.helpdesk();
    while (x != "e")
    {
        cout << "Enter a command: " << endl;
        cin >> x;
        // add
        if (x == "a")
        {
            git.add();
        }
        // print
        else if (x == "p")
        {
            git.print();
        }
        // load
        else if (x == "l")
        {
            int temp;
            cout << "Which version would you like to load?" << endl;
            cin >> temp;
            if (temp < 1 || temp > git.get_num_version())
            {
                cout << "Please enter a valid version number. If you are not sure please press 'p' to list all valid version numbers." << endl;
            }
            git.load(temp);
        }
        // compare
        else if (x == "c")
        {
            int version1, version2;
            cout << "Please enter the number of the first version to compare:\n"
                 << endl;
            cin >> version1;
            cout << "Please enter the number of the second version to compare:\n"
                 << endl;
            cin >> version2;
            git.compare(version1, version2);
        }
        // search
        else if (x == "s")
        {
            string temp;
            cout << "Please enter the keyword that you are looking for:\n"
                 << endl;
            cin >> temp;
            git.search(temp);
        }
        // remove
        else if (x == "r")
        {
            int temp;
            cout << "Enter the number of the version that you want to delete:\n"
                 << endl;
            cin >> temp;
            git.remove(temp);
        }
        // exit
        else if (x == "e")
        {
            break;
        }
        else
        {
            cout << "Please enter a valid command\n"
                 << endl;
        }
    }
    return 0;
}