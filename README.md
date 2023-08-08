# scop

_The goal of the project is to display a 3D object using modern OpenGl in C._
_No library was used for parsing obj and mtl files_

## Installation:

```sh
git clone https://github.com/wwatkins42/scop.git
cd ./scop
make
```

## Usage:
* `./scop [--color] [--position] filename.obj [filename.obj ...]`
* `--color: put color to the obj when no texture`
* `--position: put obj in original position`

## Example:
* `./scop ./resources/teapot2.obj`
* `./scop --color --position resources/Survival_BackPack_2.obj`

## Keys:
__Camera:__
* `w` and `s`: move the camera front or back
* `d` and `a`: move the camera right or left
* `e` and `q`: move the camera up or down
* `UP` and `DOWN`: rotate the camera up or down
* `RIGHT` and `LEFT`: rotate the camera right or left
* `1`, `2` and `3`: switch between 3 different cameras

__Transformation__:
* `o`: set or unset model rotation
* `j` and `n`: move the model on the x axis
* `k` and `m`: move the model on the y axis
* `l` and `,`: move the model on the z axis
* `;` and `.`: change the model size
* `shift` + `j` or `n`: rotate the model on the x axis
* `shift` + `k` or `m`: rotate the model on the y axis
* `shift` + `l` or `,`: rotate the model on the z axis

__Display__:
* `space`: switch between color and texture
* `p`: switch polygon mode between fill, line, point
* `u`: switch mode between all, material, color/texture
* `0` and `9`: change the material of the model
* `h`: set or unset normal vector mode

__Other__:
* `i`: switch the position of the light from the origin to the camera
* `y`: set or unset destruction mode

![Backpack color](https://github.com/Dunk4n/scop/blob/master/resources/img/backpack_color.png)
![Backpack texture](https://github.com/Dunk4n/scop/blob/master/resources/img/backpack_texture.png)
![Teapot normal vector](https://github.com/Dunk4n/scop/blob/master/resources/img/teapot_normal_vector.png)
![Teapot mesh](https://github.com/Dunk4n/scop/blob/master/resources/img/teapot_mesh.png)
