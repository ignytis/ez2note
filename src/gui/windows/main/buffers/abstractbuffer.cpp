#include "abstractbuffer.hpp"

using namespace Ez2note::Gui::Windows::Main::Buffers;

AbstractBuffer::AbstractBuffer(wxWindow* parent, Ez2note::Config& config)
    : wxPanel(parent, wxID_ANY), config(config) {}
