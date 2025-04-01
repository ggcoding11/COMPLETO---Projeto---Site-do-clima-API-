fetch("https://dragonball-api.com/api/characters").then(resposta =>{
    return resposta.json()
})
.then(dados =>{
    let selecaoCards = document.querySelectorAll(".card")

    selecaoCards.forEach((card, index) =>{
        let titulo = card.querySelector(".card-title")

        titulo.innerHTML = dados.items[index].name

        let imagem = card.querySelector("#foto")

        imagem.src= dados.items[index].image
    })
})
.catch(erro =>{
    console.error(erro)
})