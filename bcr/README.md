<div align="center" id="top"> 
  <img src="./assets/bcr(1).png" alt="Bar Chart" width="128px"/>

  &#xa0;

  <!-- <a href="https://sudoku.netlify.app">Demo</a> -->
</div>

<h1 align="center">Bar Chart Race</h1>

<!-- <p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/{{YOUR_GITHUB_USERNAME}}/sudoku?color=56BEB8">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/{{YOUR_GITHUB_USERNAME}}/sudoku?color=56BEB8">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/{{YOUR_GITHUB_USERNAME}}/sudoku?color=56BEB8">

  <img alt="License" src="https://img.shields.io/github/license/{{YOUR_GITHUB_USERNAME}}/sudoku?color=56BEB8"> -->

  <!-- <img alt="Github issues" src="https://img.shields.io/github/issues/{{YOUR_GITHUB_USERNAME}}/sudoku?color=56BEB8" /> -->

  <!-- <img alt="Github forks" src="https://img.shields.io/github/forks/{{YOUR_GITHUB_USERNAME}}/sudoku?color=56BEB8" /> -->

  <!-- <img alt="Github stars" src="https://img.shields.io/github/stars/{{YOUR_GITHUB_USERNAME}}/sudoku?color=56BEB8" /> -->
<!-- </p> -->

<!-- Status -->

<!-- <h4 align="center"> 
	🚧  Sudoku 🚀 Under construction...  🚧
</h4> 

<hr> -->

<p align="center">
  <a href="#dart-about">About</a> &#xa0; | &#xa0; 
  <a href="#sparkles-features">Features</a> &#xa0; | &#xa0;
  <a href="#rocket-technologies">Technologies</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="#memo-license">License</a> &#xa0; | &#xa0;
  <a href="https://github.com/fernando-ff" target="_blank">Author</a>
</p>

<br>

## :dart: About ##

A bar chart or bar graph is a chart or graph that presents categorical data with rectangular bars with heights or lengths proportional to the values that they represent. The bars can be plotted vertically or horizontally. A vertical bar chart is sometimes called a column chart.

## Git Commit Guidelines ##

### Type

Must be one of the following:

- **feat**: A new feature
- **fix**: A bug fix
- **docs**: Documentation only changes
- **style**: Changes that do not affect the meaning of the code (white-space, formatting, missing
  semi-colons, etc)
- **refactor**: A code change that neither fixes a bug nor adds a feature
- **perf**: A code change that improves performance
- **test**: Adding missing or correcting existing tests
- **chore**: Changes to the build process or auxiliary tools and libraries such as documentation
  generation
- **wip**: Work in Progress

**Example:**

```sh
git commit -m "feat: sigaa login form implemented"
```

## :rocket: Technologies ##

The following tools were used in this project:

- [C++](https://www.learncpp.com/)
- [Cmake](https://cmake.org/)
- [Doxygen](https://www.doxygen.nl/manual/starting.html)
- [Valgrind](https://valgrind.org/)
 

## :white_check_mark: Requirements ##

Before starting :checkered_flag:, you need to have [Git](https://git-scm.com) and [Cmake](https://cmake.org/) installed.

## :checkered_flag: Starting ##

```bash
# Clone this project
$ git clone ssh://git@projetos.imd.ufrn.br:4422/fernandoff/bar-chart-race.git

# Access
$ cd bar-chart-race

# to compile
$ cmake -S source -Bbuild
$ cmake --build build

# Run the project
$ ./build/bcr 

#interface
$ ./bcr [<options>] <input_data_file>
  Bar Chart Race options:
      -b  <num> Max # of bars in a single char.
                Valid range is [1,15]. Default values is 5.
      -f  <num> Animation speed in fps (frames per second).
                Valid range is [1,24]. Default value is 24.
  #for example
  $ ./bcr -b 8 -f 24 ./data/cities.txt

# Remember to execute the commands in the root
```

## :memo: License ##

This project is under license from SELAN. For more details, enter in contact with [SELAN](https://sigaa.ufrn.br/sigaa/public/docente/portal.jsf?siape=2497950).


Made with :heart: by <a href="https://github.com/fernando-ff" target="_blank">Fernando Ferreira</a>

&#xa0;

<a href="#top">Back to top</a>