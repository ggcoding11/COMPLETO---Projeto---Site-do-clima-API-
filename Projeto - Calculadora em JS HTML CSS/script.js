let expressao = ""
let display = document.getElementById("display")

document.querySelectorAll(".btn").forEach(botao => {
    botao.addEventListener("click", function () {
        let valor = this.innerText

        let valores = expressao.match(/(\d+|[\+\-\*\/])/g);

        if (valor === "C") {
            display.innerHTML = ""
            expressao = ""
        } else if (valor === "=") {
            let n1 = Number(valores[0])
            let n2 = Number(valores[2])

            if (!isNaN(n1) && !isNaN(n2)) {
                switch (valores[1]) {
                    case "+":
                        display.innerHTML = n1 + n2
                        break;
                    case "-":
                        display.innerHTML = n1 - n2
                        break;
                    case "*":
                        display.innerHTML = n1 * n2
                        break;

                    case "/":
                        display.innerHTML = n1 / n2
                        break;

                    default:
                        display.innerHTML = "Erro!"
                        break;
                }
            } else {
                display.innerHTML = "Erro!"
            }

            expressao = ""
        } else {
            expressao += valor
            display.innerHTML = expressao
        }
    })
})