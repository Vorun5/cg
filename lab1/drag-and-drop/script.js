window.addEventListener('DOMContentLoaded', () => {
    const draggable = document.getElementById('draggable')
    const width = 205
    const height = 200
    draggable.style.width = width
    draggable.style.height = height

    let x = 100
    let y = 100
    let dX = 0
    let dY = 0

    const move = () => {
        draggable.style.top = `${y}px`
        draggable.style.left = `${x}px`
    }

    move()

    draggable.addEventListener('dragstart', (event) => {
        // TODO: два Картмана
        // TODO: без этого костыля
        setTimeout(() => {
            draggable.classList.add('hide')
        }, 0)

        dX = event.clientX - x
        dY = event.clientY - y
    })

    draggable.addEventListener('dragend', (event) => {
        const clientY = event.clientY < 0 ? 0 : event.clientY
        const clientX = event.clientX < 0 ? 0 : event.clientX
        y = clientY - dY
        x = clientX - dX
        move()
        draggable.classList.remove('hide')
    })
})
