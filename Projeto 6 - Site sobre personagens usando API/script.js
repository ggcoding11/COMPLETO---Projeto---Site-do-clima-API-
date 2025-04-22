let currentPage = 1
let totalPaginas = 1
let indicePagina = document.getElementById("pagina-atual")

function carregarPersonagens(page){
    if (page < 1 || page > totalPaginas){
        return
    }

    fetch(`https://dragonball-api.com/api/characters?page=${page}`)
        .then(response => response.json())
        .then(data => {
            currentPage = page
            indicePagina.innerText = currentPage
            totalPaginas = data.meta.totalPages

            let botaoAnterior = document.getElementById("btn-anterior")

            if (currentPage == 1){
                botaoAnterior.className = "btn btn-secondary"
            } else {
                botaoAnterior.className = "btn btn-primary"
            }

            let botaoProximo = document.getElementById("btn-proximo")

            if (currentPage == totalPaginas){
                botaoProximo.className = "btn btn-secondary"
            } else {
                botaoProximo.className = "btn btn-primary"
            }

            let container = document.getElementById("container-personagens")
            container.innerHTML = ""

            data.items.forEach(function(personagem){
                let card = document.createElement("div")
                card.className = "card"
                card.innerHTML = `
                <h3>${personagem.name}</h3>
                <img src="${personagem.image}" alt="${personagem.name}">
                <p>${personagem.race}</p>

                `
                
                container.appendChild(card)

            })

            document.getElementById("btn-anterior").addEventListener("click", function(){
                carregarPersonagens(currentPage - 1)
            })

            document.getElementById("btn-proximo").addEventListener("click", function(){
                carregarPersonagens(currentPage + 1)
            })
        })
}

carregarPersonagens(currentPage)