
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <cstdio>
#endif

#include "Example.h"

ExampleStructure::ExampleStructure() : Structure(kStructureExample) {
    // An instance of the ExampleStructure class is constructed for each
    // occurrence of the "Example" structure in the OpenDDL file.
}

ExampleStructure::~ExampleStructure() {}

bool ExampleStructure::ValidateSubstructure(
    const DataDescription *dataDescription, const Structure *structure) const {
    // In this example, we only allow the "float" data structure to be
    // contained inside an "Example" structure.

    return (structure->GetStructureType() == kDataFloat);
}

ExampleDataDescription::ExampleDataDescription() {}

ExampleDataDescription::~ExampleDataDescription() {}

Structure *
ExampleDataDescription::CreateStructure(const String<> &identifier) const {
    // This function is called for each structure identifier encountered
    // in an OpenDDL file. In this example, we only recognize the identifier
    // "Example", and if matched, we return a new instance of ExampleStructure.

    if (identifier == "Example") {
        return (new ExampleStructure);
    }

    return (nullptr);
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance,
                   LPSTR commandLine, int cmdShow)
#else
int main(int argc, char *argv[])
#endif
{
    char *buffer;
    // Parse the file "Example.oddl".
#ifdef _WIN32
    HANDLE handle =
        CreateFile("Example.oddl", GENERIC_READ, FILE_SHARE_READ, nullptr,
                   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (handle != INVALID_HANDLE_VALUE) {
        DWORD actual;

        // Allocate space for the entire file plus one more byte for the zero
        // terminator.

        DWORD size = GetFileSize(handle, nullptr);
        buffer = new char[size + 1];

        // Read the entire contents of the file and put a zero terminator at the
        // end.

        ReadFile(handle, buffer, size, &actual, nullptr);
        buffer[size] = 0;
        CloseHandle(handle);
    }
#else
    // Read the file "Example.oddl" into memory.
    FILE *file = fopen("Example.oddl", "rb");
    if (file) {
        // Allocate space for the entire file plus one more byte for the zero
        // terminator.
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = new char[size + 1];
        // Read the entire contents of the file and put a zero terminator at the
        // end.
        size_t actual = fread(buffer, 1, size, file);
        fclose(file);
        buffer[size] = 0;
    }
#endif

    ExampleDataDescription exampleDataDescription;

    // Once the file is in memory, the DataDescription::ProcessText() function
    // is called to create the structure tree.

    DataResult result = exampleDataDescription.ProcessText(buffer);
    if (result == kDataOkay) {
        const Structure *structure =
        exampleDataDescription.GetRootStructure()->GetFirstSubstructure(kStructureExample);
        while (structure) {
            // This loops over all top-level structures in the file.

            // Do something with the data...
            printf("Found structure: %s\n",
                     structure->GetStructureName());

            structure = structure->GetNextSubnode();
        }
    }

    delete[] buffer;

    return (0);
}
