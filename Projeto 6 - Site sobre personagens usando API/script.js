fetch("https://dragonball-api.com/api/characters").then(resposta => {
    return resposta.json()
})
    .then(dados => {
        criarCards(dados)
    })
    .catch(erro => {
        console.error(erro)
    })

function criarCards(dados) {
    let container = document.createElement("div")
    container.className = "container mt-4"
    document.body.appendChild(container)

    for (let j = 0; j < 3; j++) {
        let row = document.createElement("div")
        row.className = "row"
        container.appendChild(row)

        for (let i = 0; i < 3; i++) {
            let col = document.createElement("div")
            col.className = "col-12 col-lg-4 mb-2"
            row.appendChild(col)

            let card = document.createElement("div")
            card.className = "card"
            col.append(card)

            let h5 = document.createElement("h5")
            h5.className = "card-title mx-auto"
            h5.id = "nome"
            card.appendChild(h5)

            let img = document.createElement("img")
            img.src = ""
            img.alt = "img-db"
            img.id = "foto"
            img.className = "mx-auto"

            card.appendChild(img)
        }

        inserirConteudo(dados)
    }
}

function inserirConteudo(dados) {
    let selecaoCards = document.querySelectorAll(".card")

    selecaoCards.forEach((card, index) => {
        let titulo = card.querySelector(".card-title")

        titulo.innerHTML = dados.items[index].name

        let imagem = card.querySelector("#foto")

        imagem.src = dados.items[index].image
    })
}