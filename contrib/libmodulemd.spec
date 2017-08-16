%global gitcommit 93dab5a25f5013ab3243efa70181a30153adfa97
%{?gitcommit:%global gitcommitshort %(c=%{gitcommit}; echo ${c:0:7})}

%global majorminorversion 0.1
#%global patchversion

Name:           libmodulemd
Version:        %{majorminorversion}%{?patchversion:.%{patchversion}}
Release:        0.2%{?gitcommit:.git%{gitcommitshort}}%{?dist}
Summary:        Module metadata manipulation library

License:        LGPLv2+
URL:            https://github.com/sgallagher/libmodulemd
%if %{defined gitcommit}
Source0:        https://github.com/sgallagher/libmodulemd/archive/%{?gitcommit}/%{name}-%{gitcommitshort}.tar.gz
%else
Source0:        https://github.com/sgallagher/libmodulemd/archive/v%{version}/%{name}-%{version}.tar.gz
%endif

BuildRequires:  meson
BuildRequires:  gcc
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(yaml-0.1)

%description
C Library for manipulating module metadata files
See https://pagure.io/modulemd for more details.

%package devel
Summary: Development files for libmodulemd
Requires: %{name} = %{version}-%{release}

%description devel
Development files for libmodulemd

%prep
%if %{defined gitcommit}
%autosetup -n %{name}-%{gitcommit} -p1
%else
%autosetup -p1
%endif

%build
%meson
%meson_build

%check
export LC_CTYPE=C.utf8
%meson_test

%install
%meson_install

%files
%license COPYING
%doc README.md
%{_libdir}/%{name}.so.*
%{_libdir}/girepository-1.0/Modulemd-%{majorminorversion}.typelib

%files devel
%{_libdir}/%{name}.so
%{_libdir}/pkgconfig/modulemd.pc
%{_includedir}/modulemd
%{_datadir}/gir-1.0/Modulemd-%{majorminorversion}.gir

%changelog
* Wed Aug 16 2017 Stephen Gallagher <sgallagh@redhat.com> - 0.1-0.2.git93dab5a
- Fix setters involving hash tables

* Wed Aug 16 2017 Stephen Gallagher <sgallagh@redhat.com> - 0.1-0.1.gitb78fd31
- Initial package

