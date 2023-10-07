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
    {
        id: 6,
        name: 'Лава',
        img: 'statics/elements/лава.png',
    },
    {
        id: 7,
        name: 'Пыль',
        img: 'statics/elements/пыль.png',
    },
    {
        id: 8,
        name: 'Порох',
        img: 'statics/elements/порох.png',
    },
    {
        id: 9,
        name: 'Взрыв',
        img: 'statics/elements/взрыв.png',
    },
    {
        id: 10,
        name: 'Дым',
        img: 'statics/elements/дым.png',
    },
    {
        id: 11,
        name: 'Энергия',
        img: 'statics/elements/энергия.png',
    },
    {
        id: 12,
        name: 'Камень',
        img: 'statics/elements/камень.png',
    },
    {
        id: 13,
        name: 'Буря',
        img: 'statics/elements/буря.png',
    },
    {
        id: 14,
        name: 'Металл',
        img: 'statics/elements/металл.png',
    },
    {
        id: 15,
        name: 'Электричество',
        img: 'statics/elements/электричество.png',
    },
    {
        id: 16,
        name: 'Водород',
        img: 'statics/elements/водород.png',
    },
    {
        id: 17,
        name: 'Кислород',
        img: 'statics/elements/кислород.png',
    },
    {
        id: 18,
        name: 'Озон',
        img: 'statics/elements/озон.png',
    },
    {
        id: 19,
        name: 'Грязь',
        img: 'statics/elements/грязь.png',
    },
    {
        id: 20,
        name: 'Гейзер',
        img: 'statics/elements/гейзер.png',
    },
    {
        id: 21,
        name: 'Паровой котел',
        img: 'statics/elements/паровой котёл.png',
    },
    {
        id: 22,
        name: 'Давление',
        img: 'statics/elements/давление.png',
    },
    {
        id: 23,
        name: 'Вулкан',
        img: 'statics/elements/вулкан.png',
    },
    {
        id: 24,
        name: 'Гремучий газ',
        img: 'statics/elements/гремучий газ.gif',
    },
    {
        id: 25,
        name: 'Болото',
        img: 'statics/elements/болото.png',
    },
    {
        id: 26,
        name: 'Спирт',
        img: 'statics/elements/спирт.png',
    },
    {
        id: 27,
        name: 'Коктель Молотова',
        img: 'statics/elements/коктель молотова.png',
    },
    {
        id: 28,
        name: 'Жизнь',
        img: 'statics/elements/жизнь.png',
    },
    {
        id: 29,
        name: 'Бактерии',
        img: 'statics/elements/бактерии.png',
    },
    {
        id: 30,
        name: 'Водка',
        img: 'statics/elements/водка.png',
    },
]

const recipes = [
    ['Пар', ['Огонь', 'Вода']],
    ['Лава', ['Огонь', 'Земля']],
    ['Пыль', ['Земля', 'Воздух']],
    ['Порох', ['Пыль', 'Огонь']],
    ['Взрыв', ['Порох', 'Огонь']],
    ['Дым', ['Порох', 'Огонь']],
    ['Энергия', ['Воздух', 'Огонь']],
    ['Пар', ['Лава', 'Вода']],
    ['Камень', ['Лава', 'Вода']],
    ['Буря', ['Воздух', 'Энергия']],
    ['Металл', ['Камень', 'Огонь']],
    ['Электричество', ['Энергия', 'Металл']],
    ['Водород', ['Вода', 'Электричество']],
    ['Кислород', ['Вода', 'Электричество']],
    ['Озон', ['Кислород', 'Электричество']],
    ['Грязь', ['Вода', 'Пыль']],
    ['Гейзер', ['Пар', 'Земля']],
    ['Паровой котел', ['Металл', 'Пар']],
    ['Давление', ['Пар', 'Паровой котел']],
    ['Вулкан', ['Давление', 'Лава']],
    ['Гремучий газ', ['Водород', 'Кислород']],
    ['Болото', ['Земля', 'Вода']],
    ['Спирт', ['Вода', 'Огонь']],
    ['Коктель Молотова', ['Спирт', 'Огонь']],
    ['Жизнь', ['Болото', 'Энергия']],
    ['Бактерии', ['Болото', 'Жизнь']],
    ['Водка', ['Вода', 'Спирт']],
]

window.addEventListener('DOMContentLoaded', () => {
    const newElementSound = new Audio(
        'https://zvukipro.com/uploads/files/2019-05/1558078572_magic-turning-spells-casting_mjtx4seu.mp3',
    )
    const elementSound = new Audio(
        'https://zvukipro.com/uploads/files/2019-03/1551688268_7aa8855faf4db26.mp3',
    )
    const gameOverSound = new Audio(
        'https://zvukipro.com/uploads/files/2020-07/1595050184_ljnn.mp3',
    )
    const notifications = document.getElementById('notifications')
    const elements = document.getElementById('elements')
    const laboratory = document.getElementById('laboratory')
    const laboratoryWrapper = document.getElementById('laboratory-wrapper')
    const deleteButton = document.getElementById('delete')
    const gameOver = document.getElementById('game-over')

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
        }, 2000)
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
        laboratoryElementBlock.style.zIndex = id

        return laboratoryElementBlock
    }

    let elementTaken
    let laboratoryElementTaken
    let elementTakenD = {
        x: 0,
        y: 0,
    }
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
        while (laboratory.firstChild) {
            laboratory.removeChild(laboratory.firstChild)
        }
        laboratoryElements = []
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
        elementTaken.style.zIndex = id
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
        setTimeout(() => (laboratoryElementTaken.style.display = 'none'), 0)
        const pos = laboratoryElementTaken.getBoundingClientRect()
        elementTakenD.x = pos.x - event.pageX
        elementTakenD.y = pos.y - event.pageY
    }
    const laboratoryElementDragEnd = (_) => {
        laboratoryElementTaken.style.display = 'block'
        laboratoryElementTaken = null
    }

    const getNewElement = (firstElement, secondElement, position) => {
        const ingredients = [firstElement.name, secondElement.name]
        ingredients.sort()
        let element
        let possibleElements = []
        recipes.forEach((recipe) => {
            const key = recipe[0]
            const value = recipe[1]
            value.sort()
            if (value.toString() === ingredients.toString()) {
                element = allElements.filter((el) => el.name === key)
                if (element.length !== 1) {
                    console.log(element)
                    return
                }
                element = element[0]
                possibleElements.push(element)
            }
        })
        if (possibleElements.length <= 0) return
        element =
            possibleElements[
                Math.floor(Math.random() * possibleElements.length)
            ]
        const firstElementBlock = document.getElementById(firstElement.id)
        if (firstElementBlock) firstElementBlock.remove()
        const secondElementBlock = document.getElementById(secondElement.id)
        if (secondElementBlock) secondElementBlock.remove()
        const id = getId()
        let elementBlock = createLaboratoryElementBlock(element, id, position)
        laboratory.append(elementBlock)
        elementBlock.addEventListener('dragstart', laboratoryElementDragStart)
        elementBlock.addEventListener('dragend', laboratoryElementDragEnd)
        laboratoryElements = laboratoryElements.filter(
            (i) => i !== firstElement.id,
        )
        laboratoryElements = laboratoryElements.filter(
            (i) => i !== secondElement.id,
        )
        laboratoryElements.push(id)

        if (!unlockedElements.includes(element)) {
            removeUnlockedElements()
            unlockedElements.push(element)
            drawUnlockedElements()
            createNotification(`Вы открыли новый элемент "${element.name}"!`)
            if (unlockedElements.length === allElements.length) {
                gameOverSound.play().catch((e) => {
                    console.log(e)
                })
                laboratoryWrapper.style.display = 'none'
                gameOver.style.display = 'block'

                return
            }
            newElementSound.play().catch((e) => {
                console.log(e)
            })
            return
        }
        elementSound.play().catch((e) => {
            console.log(e)
        })
    }

    const getElementData = (element) => {
        const id = element.getAttribute('id')
        const name = element.getElementsByTagName('img')[0].getAttribute('alt')
        return { id, name }
    }

    const laboratoryElementsDrop = (ev) => {
        const { x, y } = laboratory.getBoundingClientRect()
        if (!laboratoryElementTaken) return
        const laboratoryElementData = getElementData(ev.target.parentElement)
        const laboratoryElementTakenData = getElementData(
            laboratoryElementTaken,
        )
        if (laboratoryElementData.name === laboratoryElementTakenData.name)
            return
        getNewElement(laboratoryElementData, laboratoryElementTakenData, {
            top: `${ev.pageY - y + elementTakenD.y}px`,
            left: `${ev.pageX - x + elementTakenD.x}px`,
        })
    }

    laboratory.addEventListener('drop', (event) => {
        const { x, y } = laboratory.getBoundingClientRect()
        if (elementTaken) {
            elementTaken.style.top = `${event.pageY - y + elementTakenD.y}px`
            elementTaken.style.left = `${event.pageX - x + elementTakenD.x}px`
            laboratory.append(elementTaken)
            laboratoryElementTaken = elementTaken
            laboratoryElements.push(elementTaken.getAttribute('id'))
            elementTaken.addEventListener(
                'dragstart',
                laboratoryElementDragStart,
            )
            elementTaken.addEventListener('dragend', laboratoryElementDragEnd)
        }
        laboratory.classList.remove('laboratory__hovered')

        if (!laboratoryElementTaken) return

        for (const laboratoryElement of laboratoryElements) {
            const laboratoryElementBlock =
                document.getElementById(laboratoryElement)
            laboratoryElementBlock.removeEventListener(
                'drop',
                laboratoryElementsDrop,
            )
            laboratoryElementBlock.addEventListener(
                'drop',
                laboratoryElementsDrop,
            )
        }

        if (!laboratoryElementTaken) return
        laboratoryElementTaken.style.top = `${
            event.pageY - y + elementTakenD.y
        }px`
        laboratoryElementTaken.style.left = `${
            event.pageX - x + elementTakenD.x
        }px`
    })

    deleteButton.addEventListener('dragover', (event) => event.preventDefault())
    deleteButton.addEventListener('drop', () => {
        if (!laboratoryElementTaken) return
        const laboratoryElementTakenData = getElementData(
            laboratoryElementTaken,
        )
        laboratoryElements = laboratoryElements.filter(
            (i) => i !== laboratoryElementTakenData.id,
        )
        const laboratoryElementTakenBlock = document.getElementById(
            laboratoryElementTakenData.id,
        )
        laboratoryElementTakenBlock.remove()
    })
})
