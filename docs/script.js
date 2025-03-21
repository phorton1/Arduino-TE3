// script.js

//----------------------------------------
// onPageChanged()
//----------------------------------------


function onPageChanged(filename)
{
    // Setup the "On This Page" div

    const onThisPage = document.getElementById('on-this-page');
    onThisPage.innerHTML = '';
    const headings = document.querySelectorAll('#content h2');
    headings.forEach(heading =>
    {
        const sectionId = heading.id;
        const sectionText = heading.dataset.title ?
            heading.dataset.title : heading.textContent;
        const listItem = document.createElement('li');
        const link = document.createElement('a');
        link.href = '#' + sectionId;
        link.textContent = sectionText;
        link.addEventListener('click', function(e) {
            e.preventDefault();
            const target = document.getElementById(sectionId);
            if (target)
            {
                target.scrollIntoView({ behavior: 'smooth' });
            }
        });
        listItem.appendChild(link);
        onThisPage.appendChild(listItem);
    });

    // Add the Next link at the end of the page
    // The title defaults to that given in index.html but uses
    // the longer H1 from the file if it exists.  At the end,
    // instead of "Next - Some Title Text", the link changes to
    // "Done!! - Back to the beginning" to go back to home.htm

    let next_link = null;
    const links = document.querySelectorAll('[data-file]');
    let found = false;
    for (let link of links)
    {
        if (found)
        {
            next_link = link;
            break;
        }
        if (link.getAttribute('data-file') === filename)
            found = true;
    }

    let button_title = next_link ? "Next" : "Done!!";
    let next_title = next_link ? next_link.textContent : "Back to the beginning";
    let next_file = next_link ? next_link.getAttribute('data-file') : 'home.htm';

    fetch(next_file)
        .then(response => {
            if (!response.ok)
                return null;
            return response.text();
        })
        .then(data => {
            if (data) {
                const tempDiv = document.createElement('div');
                tempDiv.innerHTML = data;
                const titleElement = tempDiv.querySelector('h1');
                if (titleElement && next_link)
                    next_title = titleElement.textContent;
            }
        })
        .finally(() => {
            const nextA = document.createElement('a');
            nextA.href = '#';
            nextA.onclick = () => loadFileAndExpand(next_file);
            nextA.textContent = button_title;

            const nextT = document.createElement('span');
            nextT.textContent = " - " + next_title;
            // nextT.classList.add('blah');

            const nextH3 = document.createElement('h3');
            nextH3.appendChild(nextA);
            nextH3.appendChild(nextT);

            const contentArea = document.getElementById('content');
            contentArea.appendChild(document.createElement('hr'));
            contentArea.appendChild(nextH3);
        });
}



//---------------------------------------------------------------------
// Page Loading and Menu Expansion/Contraction
//---------------------------------------------------------------------

function removeSidebarSelected() {
    const activeLink = document.querySelector('.sidebar_selected');
    if (activeLink) {
        activeLink.classList.remove('sidebar_selected');
    }
}

function toggleFolderLI(event, li_element) {
    const triangle = li_element.querySelector('span'); // Get the child <span>
    const nestedList = li_element.querySelector('ul'); // Get the child <ul>
    if (triangle.classList.contains('expanded')) {
        triangle.classList.remove('expanded');
        nestedList.style.display = "none";
    } else {
        triangle.classList.add('expanded'); // Add the expanded class
        nestedList.style.display = "block";
    }
}



function loadDataFile(a_element)
    // called from index.html on elements that have the data-file attribute
{
    loadFileAndExpand(a_element.dataset.file);
}



function loadFileAndExpand(filename)
    // main public entry point to load a new page
{
    ___loadContent(filename);

    const folderLinks = document.querySelectorAll('[data-file]');
    folderLinks.forEach(link => {
        if (link.dataset.file === filename) {
            removeSidebarSelected();
            link.classList.add('sidebar_selected');
            let currentLi = link.parentNode;
            while (currentLi) {
                const triangle = currentLi.querySelector('.triangle');
                if (triangle) {
                    triangle.classList.add('expanded');
                    const nestedList = currentLi.querySelector('ul');
                    if (nestedList) {
                        nestedList.style.display = "block";
                    }
                }
                currentLi = currentLi.parentNode.closest('li');
            }
        }
    });
}



let in_hash = false;

function ___loadContent(filename)
    // private entry point to loading a new page
{
    if (in_hash) return;
    in_hash = true;

    const contentArea = document.getElementById('content');
    fetch(filename)
        .then(response => {
            if (!response.ok) throw new Error('Network response was not ok');
            return response.text();
        })
        .then(data => {
            contentArea.innerHTML = data;
            onPageChanged(filename);
            let hash_string = '#' + filename;
            if (location.hash !== hash_string) {
                history.pushState({ file: filename }, '', hash_string);
            }
        })
        .catch(error => {
            console.error('There was a problem with the fetch operation:', error);
            contentArea.innerHTML = '<br><br><p>Whoops! Sorry about that :-)</p>' +
            '<p>The page <b>' + filename + '</b> has not been created yet.';
            onPageChanged(filename);
        })
        .finally(() => {
            in_hash = false; // Reset the flag after loading
        });
}



//-------------------------------------------------------
// startJS() and system (back button) event handlers
//-------------------------------------------------------

function handleHashChange() {
    const filename = location.hash.substring(1); // Remove the '#' character
    if (filename) {
        loadFileAndExpand(filename);
    }
}

window.addEventListener('hashchange', handleHashChange);
window.addEventListener('popstate', function(event) {
    if (event.state) {
        loadFileAndExpand(event.state.file);
    } else {
        handleHashChange(); // Handle the case where there's no state
    }
});

function startJS() {
    if (location.hash) {
        handleHashChange();
    } else {
        loadFileAndExpand('home.htm'); // Load default content if no hash
    }
}

// end of script.js