#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct device_t {
    string name;
    string curres;
    vector<string> reslist;
};

vector<device_t *> getdevices() {
    char cbuffer[1024];
    vector<device_t*> devices;

    // Convert xrandr output into input stream
    FILE *fp=popen("xrandr 2>&1", "r");
    string buffer;
    while (fgets(cbuffer, 1024, fp) != NULL)
        buffer.append(cbuffer);
    pclose(fp);
    istringstream ibuffer (buffer,istringstream::in);

    string line;
    device_t *curdevice=NULL;
    while (getline(ibuffer, line)) {
        if (line.find(" connected") != string::npos) {
            char name[256];
            int resx, resy;
            int ret=sscanf(line.c_str(), "%s connected %dx%d+", name, &resx, &resy);
            if (ret > 0) {
                curdevice = new device_t();
                curdevice->name = string(name);
                if (ret == 3) {
                    stringstream ss;
                    ss << resx << "x" << resy;
                    curdevice->curres = ss.str();
                }
                devices.push_back(curdevice);
            } else curdevice = NULL;
        } else if (curdevice != NULL) {
            int resx, resy;
            if (sscanf(line.c_str(), "   %dx%d", &resx, &resy) == 2) {
                stringstream ss;
                ss << resx << "x" << resy;
                if (find(curdevice->reslist.begin(),curdevice->reslist.end(), ss.str())== curdevice->reslist.end())
                curdevice->reslist.push_back(ss.str());
            }
            else curdevice = NULL;
        } else curdevice = NULL;
    }

    return devices;
}
