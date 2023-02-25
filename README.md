<div align="center">

# `tily`

<h3>
  tily is my custom dwm configuration.
</h3>

<!-- Badges -->
![GitHub Repo stars](https://img.shields.io/github/stars/nemo256/tily?style=for-the-badge)
![Maintenance](https://shields.io/maintenance/yes/2022?style=for-the-badge)
![License](https://shields.io/github/license/nemo256/tily?style=for-the-badge)

<!-- Demo image -->
![Demo](demo.png)

</div>

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [Project Structure 📁](#project-structure)
* [Install 🔨](#install)
* [Develop ⚙️](#develop)
* [License 📑](#license)

## Project Structure 📁
```
tily/
├── patches/
│   ├── alpha.diff
│   ├── attachbottom.diff
│   ├── hide_vacant_tags.diff
│   ├── resetlayout.diff
│   ├── switchtotag.diff
│   └── vanitygaps.diff
├── AUTHORS
├── config.h
├── config.mk
├── drw.c
├── LICENSE
├── Makefile
├── movestack.c
├── README.md
├── shiftview.c
├── tily.c
├── transient.c
├── util.c
└── vanitygaps.c
```

## Install 🔨
- Download the repo:
```shell
$ cd $HOME; mkdir -p .build/
$ git clone https://github.com/nemo256/tily ~/.build/tily
$ make && sudo make clean install
```

- Add a tily entry in your .xinitrc file (here is a sample):
```shell
#!/bin/sh

exec tily
```

## Develop ⚙️
- Edit the <config.h> file.

## License 📑
- Please read [tily/LICENSE](https://github.com/nemo256/tily/blob/master/LICENSE)
