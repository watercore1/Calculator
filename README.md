# 四则运算计算器

C++ Qt 四则运算计算器 支持自定义函数和常量

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]


<!-- ABOUT THE PROJECT -->
## About The Project

![Product Name Screen Shot][product-screenshot]


<p align="right">(<a href="#top">back to top</a>)</p>


### Built With

* [Qt Creator 6.0.0(community)]()
* [Desktop_Qt_5_15_2_MinGW_64_bit ]()

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage
由于 Qt 的资源文件不能修改，而我希望用户能够自定义常量和函数。

所以 Json 文件不能作为资源文件，而是直接以相对路径读取。将 res 文件夹复制到生成的编译文件夹目录下，这样才能读写 Json 常量和 Json 函数。


<p align="right">(<a href="#top">back to top</a>)</p>


<!-- ROADMAP -->
## ROADMAP

- [x] 支持自定义常量和函数
- [x] 使用 json 文件保存，保存用户修改
- [x] 异常抛出与提示
- [ ] 复数模式和大数模式

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

Don't forget to give the project a star! Thanks again!


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>




<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/watercore1/repo_name.svg?style=flat-square
[contributors-url]: https://github.com/watercore1/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/watercore1/repo_name.svg?style=flat-square
[forks-url]: https://github.com/watercore1/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/watercore1/repo_name.svg?style=flat-square
[stars-url]: https://github.com/watercore1/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/watercore1/repo_name.svg?style=flat-square
[issues-url]: https://img.shields.io/github/issues/watercore1/repo_name.svg
[license-shield]: https://img.shields.io/github/license/watercore1/repo_name.svg?style=flat-square
[license-url]: https://github.com/watercore1/repo_name/blob/master/LICENSE.txt
[product-screenshot]: readme/screenshot.png
