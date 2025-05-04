let botaoModoEscuro = document.getElementById("botao-modo-escuro")

botaoModoEscuro.addEventListener("click", () => {
    let iconeModoEscuro = document.getElementById("icone-modo-escuro")
    let navbar = document.querySelector(".navbar")
    let tituloNavbar = document.querySelector(".navbar-brand")
    let cardsInfo = document.querySelectorAll(".info")
    let body = document.getElementsByTagName("body")[0]
    let cardContainer = document.querySelector(".card-container")

    if (botaoModoEscuro.getAttribute("aria-pressed") == "false") {
        botaoModoEscuro.setAttribute("aria-pressed", "true")
        iconeModoEscuro.className = "bi bi-moon-fill"
        navbar.className += " dark-mode"
        tituloNavbar.className += " dark-mode"
        cardsInfo.forEach(card => {
            card.className += " dark-mode"
        })

        body.style.backgroundImage = "url('/Projeto 8 - Site de clima (API)/img/img-blur-noite.png'), url('/Projeto 8 - Site de clima (API)/img/img-blur.png')";
        cardContainer.className = document.querySelector(".card-container").className.replace("white", "secondary")
    } else {
        botaoModoEscuro.setAttribute("aria-pressed", "false")
        iconeModoEscuro.className = "bi bi-moon"
        navbar.className = document.querySelector(".navbar").className.replace("dark-mode", "")
        tituloNavbar.className = document.querySelector(".navbar-brand").className.replace("dark-mode", "")

        cardsInfo.forEach(card => {
            card.className = card.className.replace(" dark-mode", "")
        })

        body.style.backgroundImage = "url('/Projeto 8 - Site de clima (API)/img/img-blur.png'), url('/Projeto 8 - Site de clima (API)/img/img-blur-noite.png')";
        cardContainer.className = document.querySelector(".card-container").className.replace("secondary", "white")
    }
})

const chaveAPI = "290fc79807794f89812162023252404"

let inputLocalPesquisado = document.getElementById("local-pesquisado")

let listaSugestoes = document.querySelector("#sugestoes")

inputLocalPesquisado.addEventListener("input", () => {
    //A cada vez que eu escrever algo, vai mostrar pra mim as sugestões (autocomplete)

    if ((inputLocalPesquisado.value).length > 2) {
        fetch(`https://api.weatherapi.com/v1/search.json?key=${chaveAPI}&q=${inputLocalPesquisado.value}`)
            .then(responseLocais => responseLocais.json())
            .then(dataLocais => {
                listaSugestoes.innerHTML = ""

                dataLocais.forEach(function (local) {
                    let sugestao = document.createElement("button")

                    sugestao.setAttribute("type", "button")

                    sugestao.className = "list-group-item list-group-item-action"

                    sugestao.innerHTML = `${local.name} - ${local.region} (${local.country})`

                    listaSugestoes.appendChild(sugestao)
                    
                    sugestao.addEventListener("mousedown", ()=>{
                        carregarInformacoes(`${local.lat},${local.lon}`)
                    })
                })
            })
    }

    if ((inputLocalPesquisado.value).length == 0) {
        listaSugestoes.innerHTML = ""
    }
})

inputLocalPesquisado.addEventListener("blur", () => {
    listaSugestoes.innerHTML = ""
})

document.getElementById("buscar-local").addEventListener("click", function () {
    carregarInformacoes(inputLocalPesquisado.value)
})

function carregarInformacoes(local) {
    fetch(`https://api.weatherapi.com/v1/current.json?key=${chaveAPI}&q=${local}`)
        .then(response => response.json())
        .then(data => {
            let condicaoAtual = data.current.condition.text

            document.getElementById("condicao-clima").innerText = condicaoAtual

            let nomeImg = condicaoAtual.toLowerCase()
            nomeImg = nomeImg.replace(/ /g, "-")
            nomeImg += ".png"

            let enderecoImg = "/Projeto 8 - Site de clima (API)/img/icones-climas/" + nomeImg

            let iconeClima = document.getElementById("icone-clima")
            iconeClima.setAttribute("src", enderecoImg)
            iconeClima.setAttribute("alt", condicaoAtual)

            document.getElementById("nome-local").innerText = (data.location.name).toUpperCase()

            let pais = data.location.country

            document.getElementById("temp-atual").innerText = data.current.temp_c + "°C"

            fetch(`https://api.weatherapi.com/v1/forecast.json?key=${chaveAPI}&q=${local}&days=1`)
                .then(responseFcast => responseFcast.json())
                .then(dataFcast => {
                    document.getElementById("temp-minima").innerText = dataFcast.forecast.forecastday[0].day.mintemp_c + "°C"
                    document.getElementById("temp-maxima").innerText = dataFcast.forecast.forecastday[0].day.maxtemp_c + "°C"
                    document.getElementById("umidade-relativa").innerText = dataFcast.forecast.forecastday[0].day.avghumidity + "%"
                })

            fetch(`https://restcountries.com/v3.1/name/${pais.toLowerCase()}`)
                .then(responseFlag => responseFlag.json())
                .then(dataFlag => {
                    let bandeiraLocal = document.getElementById("bandeira-local")
                    bandeiraLocal.setAttribute("src", dataFlag[0].flags.png)
                    bandeiraLocal.setAttribute("alt", pais)
                })
        })

        .catch(erro => {
            console.error(erro)
        })

    inputLocalPesquisado.value = ""
}

carregarInformacoes("Maringá")
