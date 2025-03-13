let expressao = ""
let display = document.getElementById("display")

document.querySelectorAll(".btn").forEach(botao => {
    botao.addEventListener("click", function () {
        let valor = this.innerHTML

        if (valor === "C") {
            display.innerHTML = ""
            expressao = ""
        } else if (valor === "=") {

        } else {

            if (valores.length < 5) {
                if (valor === "-" || valor === "*" || valor === "+" || valor === "/") {
                    expressao += " " + valor + " "
                    display.innerHTML = expressao
                } else {
                    expressao += valor
                    display.innerHTML = expressao
                }
            }
        }
    })
})