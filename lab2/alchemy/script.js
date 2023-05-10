let sortElements
let deleteLaboratoryElements

const allElements = [
    {
        id: 1,
        name: 'Огонь',
        img: 'statics/elements/огонь.gif',
    },
    {
        id: 2,
        name: 'Вода',
        img: 'statics/elements/вода.png',
    },
    {
        id: 3,
        name: 'Земля',
        img: 'statics/elements/земля.png',
    },
    {
        id: 4,
        name: 'Воздух',
        img: 'statics/elements/воздух.png',
    },
    {
        id: 5,
        name: 'Пар',
        img: 'statics/elements/пар.png',
    },
]

const recipes = new Map([['Пар', ['Огонь', 'Вода']]])

window.addEventListener('DOMContentLoaded', () => {
    const newElementSound = new Audio(
        'https://zvukipro.com/uploads/files/2019-03/1551688268_7aa8855faf4db26.mp3',
    )
    const notifications = document.getElementById('notifications')
    const elements = document.getElementById('elements')
    const laboratory = document.getElementById('laboratory')

    const getId = () => Date.now().toString()
    const createNotification = (text) => {
        const id = getId()
        const content = document.createTextNode(text)
        const notification = document.createElement('div')
        notification.classList.add('notification')
        notification.appendChild(content)
        notification.setAttribute('id', id)
        notifications.append(notification)

        setTimeout(() => {
            notification.remove()
        }, 3000)
    }
    const createElementBlock = (element, id, absolute) => {
        const elementWrapper = document.createElement('div')
        elementWrapper.classList.add('element')
        elementWrapper.setAttribute('draggable', 'true')
        if (id) elementWrapper.setAttribute('id', id)
        if (absolute)
            elementWrapper.style.position = absolute ? 'absolute' : 'static'
        const elementImg = document.createElement('img')
        elementImg.classList.add('element-img')
        elementImg.setAttribute('draggable', 'false')
        elementImg.setAttribute('alt', element.name)
        elementImg.setAttribute('src', element.img)
        const elementSpan = document.createElement('span')
        elementSpan.classList.add('element-name')
        const elementSpanText = document.createTextNode(element.name)
        elementSpan.appendChild(elementSpanText)
        elementWrapper.append(elementImg)
        elementWrapper.append(elementSpan)

        return elementWrapper
    }
    const createLaboratoryElementBlock = (element, id, position) => {
        const laboratoryElementBlock = createElementBlock(element, id, true)
        laboratoryElementBlock.classList.add('laboratory-element')
        laboratoryElementBlock.style.left = position.left
        laboratoryElementBlock.style.top = position.top

        return laboratoryElementBlock
    }

    let elementTaken
    let laboratoryElementTaken
    // Погрешность координат взятого элемента
    let elementTakenD = {
        x: 0,
        y: 0,
    }
    //  Unlocked elements
    const unlockedElements = allElements.slice(0, 4)
    document.getElementById('elements-count').innerHTML =
        allElements.length.toString()
    sortElements = () => {
        unlockedElements.sort((a, b) =>
            a.name > b.name ? 1 : b.name > a.name ? -1 : 0,
        )
        createNotification('Элементы отсортированы в алфавитном порядке')
        removeUnlockedElements()
        drawUnlockedElements()
    }
    deleteLaboratoryElements = () => {
        while (laboratory.firstChild)
            laboratory.removeChild(laboratory.firstChild)
        createNotification('Все элементы удалены из лаборатории')
    }

    const unlockedElementDragStart = (ev) => {
        const pos = ev.target.getBoundingClientRect()
        elementTakenD.x = pos.x - ev.pageX
        elementTakenD.y = pos.y - ev.pageY
        elementTaken = ev.target.cloneNode(true)
        const id = getId()
        elementTaken.setAttribute('id', id)
        elementTaken.classList.add('laboratory-element')
        elementTaken.style.zIndex = '3'
    }
    const unlockedElementDragEnd = () => {
        elementTaken = null
    }
    const removeUnlockedElements = () => {
        for (const element of unlockedElements) {
            const elementBlock = document.getElementById(element.id)
            elementBlock.removeEventListener(
                'dragstart',
                unlockedElementDragStart,
            )
            elementBlock.removeEventListener('dragend', unlockedElementDragEnd)
            elementBlock.remove()
        }
    }
    const drawUnlockedElements = () => {
        for (const element of unlockedElements) {
            const elementBlock = createElementBlock(element, element.id)
            elements.append(elementBlock)
            elementBlock.addEventListener('dragstart', unlockedElementDragStart)
            elementBlock.addEventListener('dragend', unlockedElementDragEnd)
        }
        document.getElementById('unlocked-elements-count').innerHTML =
            unlockedElements.length.toString()
    }

    drawUnlockedElements()

    laboratory.addEventListener('dragover', (event) => event.preventDefault())
    laboratory.addEventListener('dragenter', (event) => {
        event.preventDefault()
        laboratory.classList.add('laboratory__hovered')
    })
    laboratory.addEventListener('dragleave', (event) => {
        event.preventDefault()
        laboratory.classList.remove('laboratory__hovered')
    })

    let laboratoryElements = []

    const laboratoryElementDragStart = (event) => {
        laboratoryElementTaken = event.target
        const pos = laboratoryElementTaken.getBoundingClientRect()
        elementTakenD.x = pos.x - event.pageX
        elementTakenD.y = pos.y - event.pageY
    }
    const laboratoryElementDragEnd = (_) => {
        laboratoryElementTaken = null
    }

    const getNewElement = (firstElement, secondElement, position) => {
        console.log(firstElement)
        console.log(secondElement)
        const ingredients = [firstElement.name, secondElement.name]
        ingredients.sort()
        recipes.forEach((value, key) => {
            if (value.sort().toString() === ingredients.toString()) {
                const element = allElements.filter((el) => el.name === key)[0]
                document.getElementById(firstElement.id).remove()
                document.getElementById(secondElement.id).remove()
                let elementBlock = createLaboratoryElementBlock(
                    element,
                    getId(),
                    position,
                )
                laboratory.append(elementBlock)
                elementBlock.addEventListener(
                    'dragstart',
                    laboratoryElementDragStart,
                )
                elementBlock.addEventListener(
                    'dragend',
                    laboratoryElementDragEnd,
                )

                if (unlockedElements.includes(element)) return
                removeUnlockedElements()
                unlockedElements.push(element)
                drawUnlockedElements()
                createNotification(
                    `Вы открыли новый элемент "${element.name}"!`,
                )
                newElementSound.play().catch((e) => {
                    console.log(e)
                })
            }
        })
    }

    const getElementData = (element) => {
        const id = element.getAttribute('id')
        const name = element.getElementsByTagName('img')[0].getAttribute('alt')
        return { id, name }
    }

    laboratory.addEventListener('drop', (event) => {
        const { x, y } = laboratory.getBoundingClientRect()
        if (elementTaken) {
            elementTaken.style.top = `${event.pageY - y + elementTakenD.y}px`
            elementTaken.style.left = `${event.pageX - x + elementTakenD.x}px`
            laboratory.append(elementTaken)
            elementTaken.addEventListener(
                'dragstart',
                laboratoryElementDragStart,
            )
            elementTaken.addEventListener('dragend', laboratoryElementDragEnd)
        }
        laboratory.classList.remove('laboratory__hovered')

        if (!laboratoryElementTaken) return
        laboratoryElementTaken.style.top = `${
            event.pageY - y + elementTakenD.y
        }px`
        laboratoryElementTaken.style.left = `${
            event.pageX - x + elementTakenD.x
        }px`

        const newLaboratoryElements = laboratory.children
        // из за того что лаботарои элементы пусты первый раз при наведении не поялвется новый элемент
        // нужно хранить в лаборатори элемент id на элементы и когда он изменяется пересоздавать слушатели
        // или удалять/добавлять слушатели перед их добавлением/удаленим
        console.log(newLaboratoryElements)
        console.log(laboratoryElements)
        if (laboratoryElements.length === newLaboratoryElements.length) return

        const laboratoryElementsDrop = (e) => {
            const laboratoryElementData = getElementData(
                e.target.parentElement,
            )
            const laboratoryElementTakenData = getElementData(
                laboratoryElementTaken,
            )
            console.log(laboratoryElementData)
            console.log(laboratoryElementData)
            if (laboratoryElementData.name === laboratoryElementTakenData.name)
                return
            getNewElement(laboratoryElementData, laboratoryElementTakenData, {
                top: `${e.pageY - y + elementTakenD.y}px`,
                left: `${e.pageX - x + elementTakenD.x}px`,
            })
        }

        for (const laboratoryElement of laboratoryElements) {
            laboratoryElement.removeEventListener(
                'drop',
                laboratoryElementsDrop,
            )
        }
        laboratoryElements = newLaboratoryElements
        for (const laboratoryElement of laboratoryElements) {
            laboratoryElement.addEventListener('drop', laboratoryElementsDrop)
        }
    })
    // мне нужно на элементы лаборатории навестить события drag and drop
})
