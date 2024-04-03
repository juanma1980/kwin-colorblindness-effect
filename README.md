# Color Correction Filters

This effect is based on prior work of Matin Lotfaliei and Rob, authors of the KDE-Rounded-Corners effect, Kevinlekiller author of kwin-effect-shaders. Special thanks to Patricio Gonzalez Vivo for his daltonize shader of Lygia.

- ![KDE-Rounded-Corners](https://github.com/matinlotfali/KDE-Rounded-Corners)
- ![kwin-effect-shaders](https://github.com/kevinlekiller/kwin-effect-shaders)
- ![Lygia](https://github.com/patriciogonzalezvivo/lygia)

The main idea is to manipulate pixel colors with a shader for helping in color-blindness related issues.

The configuration is pretty simple, only choose the desired color correction.

# How to build from source code:

You need to install development packages for your distribution first:

<details>
<summary>Debian based (LliureX, Ubuntu, Kubuntu, KDE Neon)</summary>
<br>
    
  - Plasma 5 - by [alex47](https://github.com/alex47):
    ```
    sudo apt install git cmake g++ extra-cmake-modules kwin-dev libkf5configwidgets-dev 
    ```
  - Plasma 6
    ```
    sudo apt install git cmake g++ extra-cmake-modules kwin-dev qt6-base-dev-tools kf6-kcmutils-dev
    ```
</details>
<details>
<summary>Fedora</summary>
<br>

 - Plasma 5 (Fedora 39)
   ```bash
   sudo dnf install git cmake gcc-c++ extra-cmake-modules kwin-devel kf5-kconfigwidgets-devel libepoxy-devel
   ```
 - Plasma 6 (Fedora 40 and later)
   ```bash
   sudo dnf install git cmake gcc-c++ extra-cmake-modules kwin-devel kf6-kconfigwidgets-devel libepoxy-devel kf6-kcmutils-devel qt6-qtbase-private-devel wayland-devel
   ```
</details>
<details>
<summary>Arch - by https://github.com/hexa-one</summary>

  ```
  sudo pacman -S git cmake extra-cmake-modules base-devel
  yay -S qt5-tools
  ```
  or AUR package by [xiota](https://aur.archlinux.org/account/xiota)  
  ```
  sudo pamac build kwin-effect-rounded-corners-git
  ```
</details>
<details>
<summary>OpenSUSE - by https://github.com/mathiasgredal and https://github.com/Richardsause</summary>

  ```
  sudo zypper install git cmake gcc-c++ extra-cmake-modules libqt5-qttools-devel kconfigwidgets-devel kwindowsystem-devel kguiaddons-devel ki18n-devel knotifications-devel kwin5-devel libQt5Gui-devel libQt5OpenGL-devel libepoxy-devel libqt5-qtnetworkauth-devel
  ```
</details>
<details>
<summary>Void - by https://github.com/lay-by</summary>

  ```
  xbps-install git cmake make qt5-tools-devel extra-cmake-modules gettext-devel kwin-devel
  ```
</details>
<details>
<summary>NixOS - by https://github.com/flexagoon</summary>

   ```
   nix-env -iA nixos.kde-rounded-corners
   ```
</details>

Then clone the source code and compile it:
```bash
git clone https://github.com/lliurex/kwin-colorcorrection-effect
cd kwin-colorcorrection-effect
mkdir build
cd build
cmake .. --install-prefix /usr
make
sudo make install
```

# Load & Unload

To activate the effect, you can now log out and log back in, or run the command below inside the `build` directory:
```bash
sh ../tools/load.sh
```

To fully uninstall the effect, run the following commands inside the `build` directory:

```bash
sh ../tools/unload.sh
sudo make uninstall
```

# Auto install after KWin update

After each `kwin` package update, the effect becomes incompatible. So it won't load without a rebuild.

As long as the effect is not part of the `kwin` yet (being discussed 
[here](https://invent.kde.org/plasma/kwin/-/issues/198)), you can automate the re-installation by running the command
below inside the `build` directory:

```bash
sh ../tools/install-autorun-test.sh
```

The command above adds a `desktop` file inside the `autorun` directory which checks if the effect is still supported,
if it is not supported, it will automatically rebuild and reinstall the effect.

# Settings

You can change the color correction, or disable the effect in:

> [ System Settings ] --> [ Workspace Behavior ] --> [ Desktop Effects ] --> [ Color Correction Filters ]

![imatge](https://github.com/juanma1980/kwin-colorcorrection-effect/assets/15210634/3f094254-4f3f-4e68-a016-b1afe9a90bf3)


![imatge](https://github.com/juanma1980/kwin-colorcorrection-effect/assets/15210634/b051227b-7483-4992-948e-5455c51c7d28)


# Screenshots

RGB wheel without color correction

![imatge](https://github.com/juanma1980/kwin-colorcorrection-effect/assets/15210634/cee383be-199f-4c9f-9aaa-a2ab91065a01)


RGB wheel with protanopia_2 filter

![imatge](https://github.com/juanma1980/kwin-colorcorrection-effect/assets/15210634/eb8a5e0b-e33b-44fa-be4b-bfaf7783035b)


RGB wheel with deuteranopia_3 filter

![imatge](https://github.com/juanma1980/kwin-colorcorrection-effect/assets/15210634/a4510c3c-1c55-423c-b2a3-84d75e42c229)


RGB wheel with tritanopia_1 filter and error correction enabled

![imatge](https://github.com/juanma1980/kwin-colorcorrection-effect/assets/15210634/c4275011-6d06-46e4-ab00-a960ead03baf)


