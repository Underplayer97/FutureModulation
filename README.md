[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![project_license][license-shield]][license-url]

<div align="center">
<h1 align="center">FutureModulation</h1>
</div>

> A Linux Voice Changer that adds effects to your microphone for OBS, Discord, and other apps, using Qt and PipeWire.
> 
> Project is still in early development, nothing is built yet.


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites
* Arch
    ```bash
    pacman -S --needed base-devel cmake qt6-base pipewire
    ```

### Installation
1. Clone the repo
    ```bash
    git clone https://github.com/Underplayer97/FutureModulation.git
    ```
2. Configure the project
    ```bash
    cmake -B build -S .
    ```
3. Build the project
    ```bash
    cmake --build build
    ```

<!-- USAGE EXAMPLES -->
## Usage

TBD

<!-- ROADMAP -->
## Roadmap

- [ ] Add PipeWire Passthrough
- [ ] Add Built-in Effects
- [ ] Setup JSON Presets
- [ ] Build UI

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

Also check out [`docs/architecture.md`](docs/architecture.md) for more information.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Top contributors:

<a href="https://github.com/Underplayer97/FutureModulation/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=Underplayer97/FutureModulation" alt="contrib.rocks image" />
</a>

<!-- LICENSE -->
## License

Distributed under the GNU General Public License v3.0. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Underplayer97 - [Discord](https://discordapp.com/users/408797995077992459)

Project Link: [https://github.com/Underplayer97/FutureModulation](https://github.com/Underplayer97/FutureModulation)

<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/Underplayer97/FutureModulation.svg?style=for-the-badge
[contributors-url]: https://github.com/Underplayer97/FutureModulation/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Underplayer97/FutureModulation.svg?style=for-the-badge
[forks-url]: https://github.com/Underplayer97/FutureModulation/network/members
[stars-shield]: https://img.shields.io/github/stars/Underplayer97/FutureModulation.svg?style=for-the-badge
[stars-url]: https://github.com/Underplayer97/FutureModulation/stargazers
[issues-shield]: https://img.shields.io/github/issues/Underplayer97/FutureModulation.svg?style=for-the-badge
[issues-url]: https://github.com/Underplayer97/FutureModulation/issues
[license-shield]: https://img.shields.io/github/license/Underplayer97/FutureModulation.svg?style=for-the-badge
[license-url]: https://github.com/Underplayer97/FutureModulation/blob/main/LICENSE