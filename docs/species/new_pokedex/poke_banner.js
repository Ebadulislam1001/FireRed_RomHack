const POKEMON_COUNT = 384;
let showFront = true;
let showNames = false;

function render_sprites() {

    const list = document.getElementById("pokemon-list");
    while (list.firstChild) {
        list.removeChild(list.firstChild);
    }
    const size = document.getElementById("image_size_controller").value;
    // console.log(size);
    const font_size = size / 8;
    const img_width = size;
    const img_height = size;


    for (let i = 0; i < POKEMON_COUNT; i++) {
        let pokemon = document.createElement("div");
        pokemon.className = "flex flex-col items-center justify-center border border-black";

        if (showNames) {
            let pokemon_name = document.createElement("div");
            pokemon_name.className = "pokemon-name text-center font-bold";
            pokemon_name.innerText = (i == 231)
                ? "232_castform"
                : (i + 1) + "_" + pokemon_names[i].toLowerCase();
            pokemon.appendChild(pokemon_name);
        }

        let pokemon_sprite = document.createElement("img");
        pokemon_sprite.className = "pokemon-sprite";
        pokemon_sprite.src = (showFront)
            ? "../../../graphics/pokemon/" + pokemon_names[i].toLowerCase() + "/front.png"
            : "../../../graphics/pokemon/" + pokemon_names[i].toLowerCase() + "/back.png";
        pokemon.appendChild(pokemon_sprite);

        list.appendChild(pokemon);
    }

    let pkmn_names = document.querySelectorAll(".pokemon-name");
    // console.log(pkmn_names);
    for (let i = 0; i < pkmn_names.length; i++) {
        pkmn_names[i].style.fontSize = font_size + "px";
    }

    pkmn_sprites = document.querySelectorAll(".pokemon-sprite");
    for (let i = 0; i < pkmn_sprites.length; i++) {
        pkmn_sprites[i].style.width = img_width + "px";
        pkmn_sprites[i].style.height = img_height + "px";
    }
}
function flip_sprites() {
    showFront = !showFront;
    render_sprites();
}
function show_names() {
    showNames = !showNames;
    render_sprites();
}

document.getElementById("form").style.width = "100vw";
document.getElementById("form").style.backgroundColor = "rgb(154, 208, 161)";
document.getElementById("form").style.border = "2px solid black";
render_sprites();