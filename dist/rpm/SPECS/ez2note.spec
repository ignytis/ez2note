%define _build_id_links none
Name:           ez2note
Version:        %{_app_version}
Release:        1%{?dist}
Summary:        A simple text editor

License:        GPLv3+
URL:            https://github.com/ignytis/ez2note
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  gcc-c++
BuildRequires:  wxGTK-devel
Requires:       wxGTK

%description


%prep
%autosetup


%build
%cmake
%cmake_build


%install
# Create directories
install -d %{buildroot}%{_bindir}
install -d %{buildroot}%{_datadir}/applications
install -d %{buildroot}%{_datadir}/pixmaps

# Install binary
install -m 0755 %{_vpath_builddir}/build/ez2note %{buildroot}%{_bindir}/ez2note

# Install desktop file
install -m 0644 assets/linux/ez2note.desktop %{buildroot}%{_datadir}/applications/ez2note.desktop

# Install icon
install -m 0644 assets/icon/60_icon_256x256.png %{buildroot}%{_datadir}/pixmaps/ez2note.png


%files
%{_bindir}/ez2note
%{_datadir}/applications/ez2note.desktop
%{_datadir}/pixmaps/ez2note.png
