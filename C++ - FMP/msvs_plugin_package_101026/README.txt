------------------------------------------------------------------------
Intel(R) Threading Building Blocks Integration Plug-in - README
------------------------------------------------------------------------


Contents
--------

    - Overview
    - Installation
    - Usage
    - Integration actions
    - Advanced configuration
    - Known limitations


Overview
--------

The Intel(R) Threading Building Blocks integration plug-in provides
a simple mechanism to set up the use of Intel(R) Threading Building
Blocks (TBB) in Microsoft* Visual Studio* projects.

The plug-in can be used with C++ projects created in Microsoft*
Visual Studio* 2005, 2008 and 2010. It also works with projects
converted to use Intel(R) C++ Compiler.

Note that Microsoft* Visual Studio* 2003 is no more supported.
If you would like to use the plug-in with Microsoft* Visual Studio* 
2003 C++ projects then use a previous version. 

The TBB integration plug-in adds the following settings into
Microsoft* Visual C++* and Intel(R) C++ projects as required by TBB:

    - the path to the TBB header files
    - the path to the TBB libraries
    - the specific TBB libraries to link with
    - the specific TBB macros

See http://threadingbuildingblocks.org for full TBB documentation
and software information.


Installation
------------

Unzip the msvs_plugin.zip package and open the msvs_plugin folder that
is created.

Before use, the plug-in must be registered by performing the following
steps (depending on the version of Microsoft* Visual Studio* being used):

    - Microsoft* Visual Studio* 2005

        1.  Create or open the "<My Documents>\Visual Studio 2005\Addins"
            folder.

        2.  Copy all files from msvs_plugin\vc8 into the above folder.

    - Microsoft* Visual Studio* 2008

        1.  Create or open the "<My Documents>\Visual Studio 2008\Addins"
            folder.

        2.  Copy all files from msvs_plugin\vc9 into the above folder.

    - Microsoft* Visual Studio* 2010

        1.  Create or open the "<My Documents>\Visual Studio 2010\Addins"
            folder.

        2.  Copy all files from msvs_plugin\vc10 into the above folder.

To ensure that the registration succeeded, select Tools -> Add-in
Manager in the main Microsoft* Visual Studio* menu and check that the
TBB integration plug-in is listed in the table.  Also, the list of
installed products, in the Microsoft* Visual Studio* Help -> About
dialog, should contain an entry for "TBB Integration".

To upgrade to a new version of the TBB integration plug-in, simply
replace the previous version of the DLL installed above by the new
version.

The plugin is pre-configured to use it with commercial Intel(R) TBB 
software of versions 2.0 - 2.2, and 3.0. To use the plugin with 
open-source TBB packages, in addition to the above steps, do the 
following:

    1. Determine the full path to the root directory with the content
        of the open-source TBB package.

    2. Set TBB20_INSTALL_DIR, TBB21_INSTALL_DIR, TBB22_INSTALL_DIR or
        TBB30_INSTALL_DIR environment variable to contain the above path. 
        For instructions about how to set an environment variable, seek 
        Microsoft* Windows* help system.

See also "Advanced configuration" section for additional information.


Usage
-----

To enable TBB for a given C++ project, right-click on the project item
in the Microsoft* Visual Studio* Solution Explorer, and open the "Intel 
TBB" sub-menu in the project context menu.  The sub-menu consists of 
the following items:

    - The list of TBB versions the plugin is configured to use with.

        Click the desired version you want to use with your project to
        add the necessary parameters to the project settings.

    - "Remove Intel TBB Settings".

        Select this item to delete all TBB-specific settings from your
        project.

    - "Custom..."

        Select this item to add/delete TBB-specific settings and specify
        values of TBB-specific macros for selected configurations
        of your project.


Integration Actions
-------------------

When TBB is enabled for a C++ project as described above, the following
C++ project settings are changed:

    - The path to the TBB header files is added to "Additional Include
      Directories".

    - The path to the TBB libraries is added to "Additional Library
      Directories".

    - The TBB libraries are added into "Additional Dependencies"
      (tbb.lib for Release configuration, and tbb_debug.lib for Debug).

    - The path to the TBB dynamic libraries is appended 
      to the PATH environment variable in "Debugging | Environment".

    - TBB macros are switched on/off in "Preprocessor Definitions". 
      This functionality is only available through the Custom dialog.

The above actions are sufficient to successfully use TBB in Microsoft*
Visual Studio* C++ projects.


Advanced configuration
----------------------

The plugin takes the paths to the TBB header files and libraries from
the paths.xml file located in the directory with the plug-in DLL.
For example, the following tag structure inside paths.xml provides
the plugin with the paths for TBB 3.0 and TBB 2.2 installations:
  <TBB version_name="TBB 3.0">
    <TBB_INCLUDE_DIR>$(TBB30_INSTALL_DIR)\include</TBB_INCLUDE_DIR>
    <TBB_LIB_DIR mode="32">$(TBB30_INSTALL_DIR)\lib\ia32\vc8</TBB_LIB_DIR>
    <TBB_LIB_DIR mode="64">$(TBB30_INSTALL_DIR)\lib\intel64\vc8</TBB_LIB_DIR>
    <TBB_BIN_DIR mode="32">$(TBB30_INSTALL_DIR)\bin\ia32\vc8</TBB_BIN_DIR>
    <TBB_BIN_DIR mode="64">$(TBB30_INSTALL_DIR)\bin\intel64\vc8</TBB_BIN_DIR>
  </TBB>
  <TBB version_name="TBB 2.2">
    <TBB_INCLUDE_DIR>$(TBB22_INSTALL_DIR)\include</TBB_INCLUDE_DIR>
    <TBB_LIB_DIR mode="32">$(TBB22_INSTALL_DIR)\ia32\vc8\lib</TBB_LIB_DIR>
    <TBB_LIB_DIR mode="64">$(TBB22_INSTALL_DIR)\intel64\vc8\lib</TBB_LIB_DIR>
    <TBB_BIN_DIR mode="32">$(TBB22_INSTALL_DIR)\ia32\vc8\bin</TBB_BIN_DIR>
    <TBB_BIN_DIR mode="64">$(TBB22_INSTALL_DIR)\intel64\vc8\bin</TBB_BIN_DIR>
  </TBB>

The $(TBB30_INSTALL_DIR) is the environment variable containing the path 
to the root directory of TBB 3.0 installation; it is set automatically
when commercial TBB 3.0 package is installed, or can be set manually for
open-source packages. Likewise TBB22_INSTALL_DIR is used with TBB 2.2, etc.

Note that TBB 3.0 libraries and binaries paths are slightly different 
from paths for TBB 2.2 and earlier. Also note that for TBB 2.1 and earlier 
paths to libraries should contain "em64t" instead of "intel64".

When necessary, you can specify more TBB paths by adding new <TBB> tags 
to the configuration file. An example is provided there as a comment.
The version_name attribute should contain the text to be displayed in 
the TBB integration menu; if missed, the whole tag is ignored. If some 
directory tag under <TBB> is missed, then the corresponding setting 
will not be set during integration. If TBB_INCLUDE_DIR tag is missed, 
the corresponding item will be disabled in the TBB integration menu.

If there is no paths.xml file, the TBB integration menu will only have
the option to remove TBB settings and custom dialog item.


Known Limitations
-----------------

   - The plug-in files should not be located on a remote disk due to
     known add-in loading limitations.  For details, see
     http://msdn2.microsoft.com/en-us/library/19dax6cz(vs.80).aspx .


------------------------------------------------------------------------
INFORMATION IN THIS DOCUMENT IS PROVIDED IN CONNECTION WITH INTEL(R)
PRODUCTS.  NO LICENSE, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE, TO
ANY INTELLECTUAL PROPERTY RIGHTS IS GRANTED BY THIS DOCUMENT.  EXCEPT AS
PROVIDED IN INTEL'S TERMS AND CONDITIONS OF SALE FOR SUCH PRODUCTS,
INTEL ASSUMES NO LIABILITY WHATSOEVER, AND INTEL DISCLAIMS ANY EXPRESS
OR IMPLIED WARRANTY, RELATING TO SALE AND/OR USE OF INTEL PRODUCTS
INCLUDING LIABILITY OR WARRANTIES RELATING TO FITNESS FOR A PARTICULAR
PURPOSE, MERCHANTABILITY, OR INFRINGEMENT OF ANY PATENT, COPYRIGHT OR
OTHER INTELLECTUAL PROPERTY RIGHT.

UNLESS OTHERWISE AGREED IN WRITING BY INTEL, THE INTEL PRODUCTS ARE NOT
DESIGNED NOR INTENDED FOR ANY APPLICATION IN WHICH THE FAILURE OF THE
INTEL PRODUCT COULD CREATE A SITUATION WHERE PERSONAL INJURY OR DEATH
MAY OCCUR.  Intel may make changes to specifications and product
descriptions at any time, without notice.  Designers must not rely on
the absence or characteristics of any features or instructions marked
"reserved" or "undefined."  Intel reserves these for future definition
and shall have no responsibility whatsoever for conflicts or
incompatibilities arising from future changes to them.  The information
here is subject to change without notice.  Do not finalize a design with
this information.

The products described in this document may contain design defects or
errors known as errata which may cause the product to deviate from
published specifications.  Current characterized errata are available on
request.

Contact your local Intel sales office or your distributor to obtain the
latest specifications and before placing your product order.  Copies of
documents which have an order number and are referenced in this
document, or other Intel literature, may be obtained by calling
1-800-548-4725, or by visiting Intel's Web Site.

Intel processor numbers are not a measure of performance.  Processor
numbers differentiate features within each processor family, not across
different processor families.  See
http://www.intel.com/products/processor_number for details.

MPEG is an international standard for video compression/decompression
promoted by ISO.  Implementations of MPEG CODECs, or MPEG enabled
platforms may require licenses from various entities, including Intel
Corporation.

BunnyPeople, Celeron, Celeron Inside, Centrino, Centrino Atom, Centrino
Atom Inside, Centrino Inside, Centrino logo, Core Inside, FlashFile,
i960, InstantIP, Intel, Intel logo, Intel386, Intel486, IntelDX2,
IntelDX4, IntelSX2, Intel Atom, Intel Atom Inside, Intel Core, Intel
Inside, Intel Inside logo, Intel. Leap ahead., Intel. Leap ahead. logo,
Intel NetBurst, Intel NetMerge, Intel NetStructure, Intel SingleDriver,
Intel SpeedStep, Intel StrataFlash, Intel Viiv, Intel vPro, Intel
XScale, Itanium, Itanium Inside, MCS, MMX, Oplus, OverDrive, PDCharm,
Pentium, Pentium Inside, skoool, Sound Mark, The Journey Inside, Viiv
Inside, vPro Inside, VTune, Xeon, and Xeon Inside are trademarks of
Intel Corporation in the U.S. and other countries.

* Other names and brands may be claimed as the property of others.

Copyright (C) 2005-2010, Intel Corporation.  All rights reserved.
