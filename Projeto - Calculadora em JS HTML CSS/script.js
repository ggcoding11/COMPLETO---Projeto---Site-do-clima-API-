let display = document.getElementById("display")

let expressao = ""

document.querySelectorAll(".btn").forEach(botao => {
    botao.addEventListener("click", function(){
        let valor = this.innerHTML

        if (valor === "="){
            try {
                let resultado = eval(expressao)
                display.innerHTML = resultado
            } catch(erro){
                display.innerHTML = "Erro!"
                expressao = ""
            }
        } else if (valor === "C"){
            display.innerHTML = ""
            expressao = ""
        } else {
            expressao += valor
            display.innerHTML = expressao
        }
    })
})