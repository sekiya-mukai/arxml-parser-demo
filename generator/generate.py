from pathlib import Path

import yaml

from jinja2 import Environment
from jinja2 import FileSystemLoader


PROJECT_ROOT = Path(__file__).parent.parent

CONFIG_FILE = PROJECT_ROOT / "config" / "app.yaml"

TEMPLATE_DIR = PROJECT_ROOT / "templates"

OUTPUT_DIR = PROJECT_ROOT / "generated"


INCLUDE_DIR = OUTPUT_DIR / "include"
SRC_DIR = OUTPUT_DIR / "src"


def create_output_directories():

    OUTPUT_DIR.mkdir(exist_ok=True)

    INCLUDE_DIR.mkdir(exist_ok=True)

    SRC_DIR.mkdir(exist_ok=True)


def load_config():

    with open(
        CONFIG_FILE,
        "r",
        encoding="utf-8",
    ) as file:

        return yaml.safe_load(file)


def render_template(
    env,
    template_name,
    output_path,
    config,
):
    template = env.get_template(
        template_name
    )

    content = template.render(config)

    with open(
        output_path,
        "w",
        encoding="utf-8",
    ) as file:

        file.write(content)

    print(
        f"Generated : {output_path}"
    )


def main():

    create_output_directories()

    config = load_config()

    env = Environment(
        loader=FileSystemLoader(
            TEMPLATE_DIR
        ),
        trim_blocks=True,
        lstrip_blocks=True,
    )

    render_template(
    env,
    "src/SenderMain.cpp.j2",
    SRC_DIR / "SenderMain.cpp",
    config,
    )

    render_template(
        env,
        "src/ReceiverMain.cpp.j2",
        SRC_DIR / "ReceiverMain.cpp",
        config,
    )

    render_template(
        env,
        "include/Sender.hpp.j2",
        INCLUDE_DIR / "Sender.hpp",
        config,
    )

    render_template(
        env,
        "src/Sender.cpp.j2",
        SRC_DIR / "Sender.cpp",
        config,
    )

    render_template(
        env,
        "include/Receiver.hpp.j2",
        INCLUDE_DIR / "Receiver.hpp",
        config,
    )

    render_template(
        env,
        "src/Receiver.cpp.j2",
        SRC_DIR / "Receiver.cpp",
        config,
    )

    render_template(
        env,
        "arxml/Communication.arxml.j2",
        OUTPUT_DIR /
        f"{config['application']['name']}.arxml",
        config,
    )

    render_template(
        env,
        "CMakeLists.txt.j2",
        OUTPUT_DIR /
        "CMakeLists.txt",
        config,
    )


if __name__ == "__main__":
    main()
