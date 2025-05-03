#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void print_result(const string &algo, const vector<int> &order, int total_seek)
{
  cout << "\n--- " << algo << " ---" << endl;
  cout << "Seek Sequence: ";
  for (int pos : order)
    cout << pos << " ";
  cout << "\nTotal Seek Time: " << total_seek << " cylinders\n";
}

int fcfs(const vector<int> &requests, int head, vector<int> &order)
{
  int seek = 0;
  int current = head;
  for (int req : requests)
  {
    seek += abs(current - req);
    order.push_back(req);
    current = req;
  }
  return seek;
}

int scan(vector<int> requests, int head, int cylinders, vector<int> &order, bool direction_up = true)
{
  int seek = 0;
  requests.push_back(head);
  sort(requests.begin(), requests.end());
  int index = find(requests.begin(), requests.end(), head) - requests.begin();

  if (direction_up)
  {
    for (int i = index; i < requests.size(); ++i)
      order.push_back(requests[i]);
    if (order.back() != cylinders - 1)
      order.push_back(cylinders - 1);
    for (int i = index - 1; i >= 0; --i)
      order.push_back(requests[i]);
  }
  else
  {
    for (int i = index; i >= 0; --i)
      order.push_back(requests[i]);
    if (order.back() != 0)
      order.push_back(0);
    for (int i = index + 1; i < requests.size(); ++i)
      order.push_back(requests[i]);
  }

  int current = head;
  for (int pos : order)
  {
    seek += abs(current - pos);
    current = pos;
  }
  return seek;
}

int c_scan(vector<int> requests, int head, int cylinders, vector<int> &order)
{
  int seek = 0;
  requests.push_back(head);
  sort(requests.begin(), requests.end());
  int index = find(requests.begin(), requests.end(), head) - requests.begin();

  for (int i = index; i < requests.size(); ++i)
    order.push_back(requests[i]);
  if (order.back() != cylinders - 1)
    order.push_back(cylinders - 1);
  order.push_back(0);
  for (int i = 0; i < index; ++i)
    order.push_back(requests[i]);

  int current = head;
  for (int pos : order)
  {
    seek += abs(current - pos);
    current = pos;
  }
  return seek;
}

int main()
{
  int queue_size, initial_head, cylinders;
  string algorithm;
  vector<int> requests;

  cout << "\nDick Schedular CLI\n";
  cout << "Enter number of cylinders: ";
  cin >> cylinders;

  cout << "Enter queue size: ";
  cin >> queue_size;

  cout << "Enter request queue (space-separated): ";
  for (int i = 0; i < queue_size; ++i)
  {
    int req;
    cin >> req;
    if (req >= 0 && req < cylinders)
      requests.push_back(req);
    else
    {
      cout << "Invalid request: " << req << " ignored.\n";
      --i;
    }
  }

  cout << "Enter initial head position: ";
  cin >> initial_head;

  cout << "Enter algorithm (FCFS / SCAN / C-SCAN): ";
  cin >> algorithm;

  vector<int> seek_order;
  int total_seek = 0;

  if (algorithm == "FCFS" || algorithm == "fcfs")
    total_seek = fcfs(requests, initial_head, seek_order);
  else if (algorithm == "SCAN" || algorithm == "scan")
    total_seek = scan(requests, initial_head, cylinders, seek_order, true);
  else if (algorithm == "C-SCAN" || algorithm == "c-scan")
    total_seek = c_scan(requests, initial_head, cylinders, seek_order);
  else
  {
    cout << "Invalid algorithm name." << endl;
    return 1;
  }

  print_result(algorithm, seek_order, total_seek);

  return 0;
}
