let display = document.getElementById("display")
let expressao = ""
let n1 = ""
let n2 = ""

let operacaoFeita = false
let operacaoCarac = ""

document.querySelectorAll(".btn").forEach(botao => {
    botao.addEventListener("click", function () {
        let valor = this.innerText

        if (operacaoFeita === false) {
            if (!isNaN(Number(valor))) {
                n1 += valor
                expressao += valor
            } else if (valor === "+" || valor === "-" || valor === "*" || valor === "/") {
                operacaoFeita = true
                operacaoCarac = valor
                expressao += valor
            }
        } else {
            if (!isNaN(Number(valor))){
                n2 += valor
                expressao += valor
            }
        }

        if (valor === "C"){
            expressao = ""
            operacaoFeita = false
            operacaoCarac = ""
            n1 = ""
            n2 = ""
        }

        if (valor === "="){
            if (operacaoCarac === "+" || operacaoCarac === "-" || operacaoCarac === "*" || operacaoCarac === "/"){
                
                n1 = Number(n1)
                n2 = Number(n2)
                
                switch(operacaoCarac){
                    case "+":
                        expressao = n1 + n2
                    break

                    case "-":
                        expressao = n1 - n2
                    break

                    case "*":
                        expressao = n1 * n2
                    break

                    case "/":
                        expressao = n1 / n2
                    break
                }
            } 
        }
        
        display.innerText = expressao
    })
})